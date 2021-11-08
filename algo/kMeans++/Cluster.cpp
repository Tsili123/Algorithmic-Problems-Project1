#include "Cluster.hpp"

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

extern Cluster *cluster;

Cluster::Cluster(string input, string config, string out, bool comp, string method)
                :input_file(input), config_file(config), output_file(out), complete(comp), Method(method) {
                    
                    read_config(config);
                    this->num_of_Items = num_of_points();
                }

void Cluster::read_config(string config_file) {
    ifstream Config_File(config_file);

    if (Config_File.is_open()) {
        string Line;
        while(getline(Config_File, Line)) {
            stringstream s;
            s << Line;
            string name;
            s >> name;
            string var;
            s << Line;
            s >> var;
            name.pop_back();
            if (name == "number_of_clusters") this->number_of_clusters = stoi(var);
            else if (name == "number_of_vector_hash_tables") this->L = stoi(var);
            else if (name == "number_of_vector_hash_functions") this->k = stoi(var);
            else if (name == "max_number_M_hypercube") this->max_number_M_hypercube = stoi(var);
            else if (name == "number_of_hypercube_dimensions") this->number_of_hypercube_dimensions = stoi(var);
            else if (name == "number_of_probes") this->number_of_probes = stoi(var);
        }
        
    }
}

void Cluster::kMeanspp_Initialization() {
    int t = 1, input_items = this->num_of_Items;

    auto begin = high_resolution_clock::now();

    // Pick a random input index
    srand(time(0));
    random_device generator;
	uniform_int_distribution<int> dis(0, input_items);

	int random_index = dis(generator);

    this->centroids.push_back(random_index);

    long double P = 0.0;
    long int next_max_D = -1;

    while(t != this->number_of_clusters) {
        long double sum_min_dists = 0.0;
        long int previous_max_D = next_max_D;
        next_max_D = -1;
        vector<pair<int, long double>> prob;
        for (int point = 0; point < input_items; point++) {
            // If point is not a centroid
            if (none_of(this->centroids.begin(), this->centroids.end(), [point](int centroid) { return point == centroid; })) {
                long double dis = (long double) NUM;
                int potential_centroid = -1;
                // Find the closest centroid to the point
                for (auto centroid: this->centroids) {
                    long double point_dist;
                    if (P == 0.0) point_dist = euclidean_dis(this->data[point], this->data[centroid]);
                    else {
                        random_device generator;
                        uniform_real_distribution<float> distance(0.0, P);

                        point_dist = distance(generator);
                        point_dist /= previous_max_D;
                    }

                    if (point_dist < dis) {
                        dis = point_dist;
                        potential_centroid = point;
                    }
                }

                // Keep max distance
                if (dis > next_max_D) next_max_D = dis;

                sum_min_dists += dis;

                // Store the min distance and the point
                prob.push_back(make_pair(potential_centroid, dis));
            }
        }

        P = sum_min_dists;

        long double highest_prob = -1;
        int next_centroid = -1;
        // The point with the highest probability with be the next centroid
        // Probability = distance/sum of distances
        for (auto item: prob) {
            long double prob = item.second/P;
            if (prob > highest_prob) {
                highest_prob = prob;
                next_centroid = item.first;
            }
        }

        this->centroids.push_back(next_centroid);

        t++;
    }

    auto end = high_resolution_clock::now();
    duration<double, std::milli> time = end - begin;

    cout << "kMeans++ TIME: " << time.count() << endl;
}

vector<int> Cluster::Calculate_Mean(vector<int> near_points) {
    long int T = near_points.size();
    int size = this->data[0].size();
    vector<int> centroid(size, 0);
    for (auto point: near_points) {
        for(int i = 1; i < size; i++) {
            // cout << sum[i] << ", ";
            centroid[i] += this->data[point][i];
            // cout << sum[i] << ", " << (long double) this->data[point][i] << endl;
        }
    }

    for (int i = 1; i < size; i++) {
        centroid[i] = centroid[i]/T;
    }

    return centroid;
}

// This function compares all new clusters to their previous
// if the clusters have not changed much then return false else return true
bool Cluster::Compare(vector<vector<int>> previous_clusters) {
    for (int centroid = 0; centroid < number_of_clusters; centroid++) {
        double sum_of_diff_points = 0.0;
        int size = previous_clusters[centroid].size();
        if (size == 0) return true;
        for (int point = 1; point < size; point++) {
            if (Lloyd[centroid].first[point] != previous_clusters[centroid][point]) {
                sum_of_diff_points++;
            }
        }

        // If 10% of the cluster has changed return true
        double percentage = sum_of_diff_points/(double) (size - 1);
        if (percentage >= 0.01) return true;
    }

    return false;
}

void Cluster::Lloyd_method() {

    vector<int> empty_vec;
    empty_vec.clear();
    for (auto centroid: centroids) {
        Lloyd.push_back(make_pair(this->data[centroid], empty_vec));
    }

    centroids.clear();

    auto begin = high_resolution_clock::now();

    vector<vector<int>> previous_clusters(number_of_clusters, empty_vec);
    // previous_clusters.clear();
    // Do this until there is almost no difference to the centroids
    while (Compare(previous_clusters)) {
        // Assign each point to its centroid
        for (int centroid = 0; centroid < number_of_clusters; centroid++) {
            Lloyd[centroid].second.clear();
        }
        for (int point = 0; point < num_of_Items; point++) {
            long double dis = (long double) NUM;
            int point_centroid = -1;
            if (none_of(this->centroids.begin(), this->centroids.end(), [point](int centroid) { return point == centroid; })) {
                for (int centroid = 0; centroid < number_of_clusters; centroid++) {
                    long double point_dist = euclidean_dis(this->data[point], Lloyd[centroid].first);
                    if (point_dist < dis) {
                        dis = point_dist;
                        point_centroid = centroid;
                    }
                }

                Lloyd[point_centroid].second.push_back(point);
            }
        }

        // Store previous clusters before Updating them
        // Update centroids
        for (int centroid = 0; centroid < number_of_clusters; centroid++) {
            previous_clusters[centroid] = Lloyd[centroid].first;
            Lloyd[centroid].first = Calculate_Mean(Lloyd[centroid].second);
        }
    }

    auto end = high_resolution_clock::now();
    Cluster_time = end - begin;
}

void Cluster::Silhouette() {
    vector<long double> sil(number_of_clusters, 0);
    auto begin = high_resolution_clock::now();

    unordered_map<string, long double> dists;

    for (int cluster = 0; cluster < number_of_clusters; cluster++) {
        int size_of_cluster = Lloyd[cluster].second.size();
        vector<int> Points = Lloyd[cluster].second;
        for (auto i: Points) {
            // Calculate average distance
            long double a = 0.0;
            for (auto j: Points) {
                if (i != j) {
                    unordered_map<string, long double>::iterator it = dists.find(to_string(i)+to_string(j));
                    if (it != dists.end()) {
                        a += it->second;
                    }
                    else {
                        unordered_map<string, long double>::iterator it = dists.find(to_string(j)+to_string(i));
                        if (it != dists.end()) {
                            a += it->second;
                        } else {
                            long double euc_dis = euclidean_dis(this->data[i], this->data[j]);
                            a += euc_dis;
                            dists[to_string(i)+to_string(j)] = euc_dis;
                        }
                    }
                }
            }

            a /= (size_of_cluster-1); // average distance of i to objects in same cluster

            // Find Second closest centroid
            long double dist = NUM;
            int sec_cluster = -1;
            for (int second_cluster = 0; second_cluster < number_of_clusters; second_cluster++) {
                if (cluster != second_cluster) {
                    long double point_dist = euclidean_dis(this->data[i], Lloyd[second_cluster].first);
                    if (dist > point_dist) {
                        sec_cluster = second_cluster;
                        dist = point_dist;
                    }
                }
            }

            // Calculate average distance of second cluster
            long double b = 0.0;
            for (auto j: Lloyd[sec_cluster].second) {
                if (i != j) {
                    unordered_map<string, long double>::iterator it = dists.find(to_string(i)+to_string(j));
                    if (it != dists.end()) {
                        b += it->second;
                    }
                    else {
                        unordered_map<string, long double>::iterator it = dists.find(to_string(j)+to_string(i));
                        if (it != dists.end()) {
                            b += it->second;
                        } else {
                            long double euc_dis = euclidean_dis(this->data[i], this->data[j]);
                            b += euc_dis;
                            dists[to_string(i)+to_string(j)] = euc_dis;
                        }
                    }
                }
            }

            b /= (Lloyd[sec_cluster].second.size()-1);

            // Calculate Silhouette
            sil[cluster] += (b - a) / (b > a ? b : a);
            // cout << sil[i] << ", " << a << ", " << b << endl;
        }

        sil[cluster] /= size_of_cluster;
        // cout << cluster << ": " << sil[cluster] << endl;
    }

    this->s = sil;

    auto end = high_resolution_clock::now();
    duration<double, std::milli> time = end - begin;
    
    cout << "Silhouette TIME: " << time.count() << endl;
}

//compute the nearest center for a given vector
// int Cluster::nearest_centroid(vector<int> vec) {
// 	int min_dist = (int)INT_MAX;
// 	int nearest = -1;
// 	// compute the distances to all the centroids
// 	for (int i = 0; i < k; i++) {
// 		int dist = metrics::ManhatanDistance(vec, centroids.at(i), space_dim);
// 		// set it as min
// 		if (dist < min_dist) {
// 			min_dist = dist;
// 			nearest = i;
// 		}
// 	}
// 	assert(nearest != -1);

// 	return nearest;
// };

// // compute how many unassigned vectors we've got, for the reverse assignement method
// int Cluster::count_unassigned(vector<int> assigned) {
// 	int res = 0;
// 	for (int i = 0; i < n_points; i++) {
// 		if (assigned.at(i) == UNASSIGNED) {
// 			res++;
// 		}
// 	}
// 	return res;
// }

// // compute the minimum of the distances of the centroids. Needed for the initialization of the radius in reverse assignment
// int  Cluster::min_dist_between_centroids() {
// 	// initialize the min distance
// 	int min_dist = (int)INT_MAX;
// 	// brute force all the distances in order to find the smallest

// 	for (int i = 0; i < k; i++) {
// 		for (int j = 0; j < k; j++) {
// 			if (i != j) {
// 				int dist = metrics::ManhatanDistance(centroids.at(i), centroids.at(j), space_dim);
// 				if (dist < min_dist)
// 					min_dist = dist;
// 			}
// 		}
// 	} 
// 	return min_dist;
// }

// int reverse_assignment(void) {
// 	// keep a vector of the new assignments
// 	vector<int> new_assigned(n_points, -1);

// 	// initial radius
// 	int radius = min_dist_between_centroids() / 2;

// 	// keep track of the changes
// 	int changes = 0;

// 	// set a threshold in order to break the loop
// 	int prev_unassigned = INT_MAX;

// 	// keep track of unassinged points
// 	int unassinged = INT_MAX - 1;

// 	// break the loop when all the balls contain no new vectors
// 	while (unassinged != prev_unassigned) {
// 	// do a range search query for every centroid
				
//         for (int i = 0; i < k; i++) {

// 			list<pair<int, int>> result;
			
//             // the type of range search depends on what the user wants
// 			if (assignment_method == "reverse_LSH")
// 				result = lsh_instant->RangeSearch(centroids.at(i), radius, 1);
// 			else if (assignment_method == "reverse_Hypercube")
// 				result = hc_instant->RNeighbors(centroids.at(i), radius, 1);

// 			// iterate all the results
// 			typename std::list<std::pair<int,T>>::iterator pair_it;
					
//             for (pair_it = result.begin(); pair_it !=result.end(); pair_it++) {
// 				// get the current vector
// 				int curr_vec = pair_it->first;

// 				// if it is still unassigned
// 				if (new_assigned.at(curr_vec) == -1) {
// 					// temporarly assign it to this centroid
// 					new_assigned.at(curr_vec) = i;
// 				}// if it has been already assigned
// 				else {
// 					// chcek if its distance from the current centroid, is less than the previous' one
// 					int prev_assigned = new_assigned.at(curr_vec); 
// 					T prev_dist = metrics::ManhatanDistance(feature_vectors.at(curr_vec), centroids.at(prev_assigned), space_dim);
// 					T new_dist = pair_it->second;
// 					// if it is, it is closest to the current centroid, thus change the asssigned value in the temp vector
// 					if (new_dist < prev_dist)
// 						new_assigned.at(curr_vec) = i;
// 				}
// 			}
// 		}

// 		// update the unassigned vectors count
// 		prev_unassigned = unassinged;
// 		unassinged = count_unassigned(new_assigned);
// 		// update the radius
// 		radius *= 2;
	// }

			
//     // update the untracked vectors, and check for new changes
// 	for (int i = 0; i < n_points; i++) {
// 	// for each one not tracked, use direct assignment
// 	if (new_assigned.at(i) == UNASSIGNED)
// 			new_assigned.at(i) = nearest_centroid(feature_vectors.at(i));
// 		    // check for changes
// 			if (assigned_centroid.at(i) != new_assigned.at(i))
// 					changes++;
// 			}

// 			// update the assigned vector
// 			assigned_centroid = new_assigned;
// 			return changes;
// };


void Cluster::print() {
    cout << "number_of_clusters: " << number_of_clusters << endl;
    cout << "number_of_vector_hash_tables: " << L << endl;
    cout << "number_of_vector_hash_functions: " << k << endl;
    cout << "max_number_M_hypercube: " << max_number_M_hypercube << endl;
    cout << "number_of_hypercube_dimensions: " << number_of_hypercube_dimensions << endl;
    cout << "number_of_probes: " << number_of_probes << endl;
}

void Cluster::output() {
    ofstream Output;
    Output.open (this->output_file, ofstream::out | ofstream::trunc);
    Output << "Algorithm: ";
    if (this->Method == "Classic" || this->Method == "Lloyd") Output << "Lloyds";
    else if (this->Method == "LSH") Output << "Range Search LSH";
    else if (this->Method == "Hypercube") Output << "Range Search Hypercube";
    Output << endl;

    int counter = 1;
    for (auto centroid: this->Lloyd) {
        bool first = true;
        Output << "CLUSTER-" << counter << " {size: " << centroid.second.size() << ", centroid: ";
        for (auto points: centroid.first) {
            if (first) {
                first = false;
                continue;
            }
            Output << points << ", ";
        }
        if (this->complete) {
            Output << "Items: ";
            for (auto points: centroid.second) {
                Output << points << ", ";
            }
        }
        Output << "}" << endl;
        counter++;
    }

    Output << "cluster_time: " << this->Cluster_time.count() << endl;
    Output << "Silhouette: [";

    long double stotal = 0.0;
    for (auto cluster: this->s) {
        Output << cluster << ",";
        stotal += cluster;
    }

    Output << stotal/this->number_of_clusters << "]" << endl;

    Output.close();
}

// Calculate Euclidean Distance
long double euclidean_dis(vector<int> vec1, vector<int> vec2) {
    long double dist=0.0;

    auto itA = vec1.begin();
    auto itB = vec2.begin();
    ++itA;
    ++itB;

    while(itA != vec1.end() || itB != vec2.end())
    {
        dist = dist + (itA[0]-itB[0])*(itA[0]-itB[0]);
        if(itA != vec1.end()) {
            ++itA;
        }
        if(itB != vec2.end()) {
            ++itB;
        }
    }

	return sqrt(dist);
}