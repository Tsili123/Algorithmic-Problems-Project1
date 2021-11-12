#include "./hypercube.hpp"

using namespace std;

Hypercube::Hypercube(string input_, std::string query_, std::string output_,int R_,int k_,int threshold_, 
		int points_num_,int N_,int space_,int max_probes_,std::vector<std::vector<int>> data_vectors_) :input_file(input_), query_file(query_), output_file(output_),
		R(R_),k(k_), threshold(threshold_), points_num(points_num_),N(N_),space(space_),max_probes(max_probes_),data_vectors(data_vectors_) {
			
            //measure the time that it takes to initialize the hypercube
            time_t start, finish;
            //fprintf(stdout, "Hypercube program with parameters:  k = %d, threshold = %d points_num = %d, space = %d, max_probes = %d,", k, threshold, points_num, space, max_probes);
            time(&start);

            // we have a bitstring of k bits, thus the size of the hypercube table will be 2^k
            buckets_num = (int)pow(2, k);

			long double sum = 0;
			int subpoints = this->points_num * 5/100;
			for (int point = 1; point < subpoints - 1; point++) {
				for (int second_point = point; second_point < subpoints; second_point++) {
					sum += euclidean_dis(data_vectors[point], data_vectors[second_point]);
				}
				sum /= (subpoints - point);
			}

			//Create hash functions for each bucket
            this->H_i_ptr = new Euclidean_H_i(k,space, sum);

			// Set size of H
        	this->Hi_map.reserve(k_);
			this->hypercube.reserve(this->buckets_num);

			for(int i=0;i<this->k;i++){
    			f_i.push_back(uniform_int_distribution<int>(0,1));
				this->Hi_map.push_back(unordered_map<int, bool>());
			}

            // initialize the hypercube hashtable
            //every bucket contains a list of integers
            //each one integers means the id of the point at the data
            // for example : the number 2 means the second point etc ..
            for (int i = 0; i < buckets_num; i++) {
                std::list<int> temp_list;
                hypercube.push_back(temp_list);
            }
			
			//cout << points_num << endl;
			//insert all of the points into the hypercube
			for (int i = 0; i < points_num; i++) {
				int bucket_id = hypercube_hash(data_vectors.at(i));
				this->hypercube[bucket_id].push_back(i);
			}

			// hypercube initialization done. print the time differenct

			time(&finish);
			std::cout << " Hypercube created in " << difftime(finish, start) << " sec" << std::endl;
		}

Hypercube::~Hypercube() {
    for (int i = 0; i < points_num; i++) {
        int bucket_id = hypercube_hash(data_vectors.at(i));
        this->hypercube[bucket_id].clear();
    }

    delete H_i_ptr;

    data_vectors.clear();
};

int Hypercube::hypercube_hash(std::vector<int> vec_point){
    // store the string produced
    std::string bucket_string = "";
    int curr_Hi;
    bool curr_Fi;
    std::unordered_map<int, bool>::const_iterator iterh; // Iterate through map
    std::default_random_engine generator;

    // hash k times
    for(int i=0;i<this->k;i++){
            // hash with the i-th hash fn

            curr_Hi = this->H_i_ptr->Specific_Hi(vec_point,i);
            // Find if H[i] value exists 
            iterh = this->Hi_map[i].find(curr_Hi);

            // Exists 
            if(iterh != this->Hi_map[i].end())
                curr_Fi = iterh->second;
            // Map current H[i] and add it in the map 
            else{
                curr_Fi = this->f_i[i](generator);
                this->Hi_map[i].insert(std::pair<int, bool>(curr_Hi, curr_Fi));
            }
                bucket_string += std::to_string(curr_Fi);
    }

    // convert the bitstring into an integer
    return stoi(bucket_string, nullptr, 2);
}

int Hypercube::hammingDistance(int n1, int n2) {
    int x = n1 ^ n2;
    int setBits = 0;

    while (x > 0) {
        setBits += x & 1;
        x >>= 1;
    }

    return setBits;
}

void Hypercube::RNeighbors(std::vector<int> query, int radius, std::list<int>& neighbors, std::list<double>& neighbors_dists) { 
    int i, cube_id, pos;
    double curr_Dist; // Distance of a point in list
    std::vector<Neighbor_Vertice> Neighbor_Vertices; // Keep all neighbors  
    int neighbors_num = 0; 
    
    // Clear given lists 
    //neighbors.clear();
    //if(neighbors_dists != NULL)
    //	neighbors_dists->clear();

    // Find initial vertice 
    cube_id = hypercube_hash(query);

    // Find all neighbors of that vertice 
    for(i = 0; i < this->buckets_num; i++){

        // Don't check the same position 
        if(i == cube_id)
            continue;

        Neighbor_Vertices.push_back(Neighbor_Vertice(hammingDistance(cube_id, i), i));
    }

    // Sort Neighbor Vertices 
    make_heap(Neighbor_Vertices.begin(), Neighbor_Vertices.end(), Compare_Vertices());//, Compare_Vertices()
    sort_heap(Neighbor_Vertices.begin(), Neighbor_Vertices.end(), Compare_Vertices());

    //  for(i = 0; i < this->buckets_num; i++){
    //  	std::cout << Neighbor_Vertices[i].id << " ";
    // }
    //std::cout << "probes" << this->max_probes  ;

    // Check probes vertices for neighbors 
    for(i = 0; i < this->max_probes; i++){

        // Check initial pos 
        if(i == 0)
            pos = cube_id;
        // Extract minimum position
        else
            pos = Neighbor_Vertices[i-1].id;

        // Empty vertice(bucket) 
        if(this->hypercube[pos].size() == 0){
            //cout << "here " << i << "\n";
            continue;
        }

        // Scan current vertice 
        for(auto iter = this->hypercube[pos].begin(); iter != this->hypercube[pos].end(); iter++){  
            neighbors_num += 1;
            
            // Find current distance 
            curr_Dist = euclidean_dis(data_vectors.at(*iter),query);

            // Keep neighbor 
            if(curr_Dist < radius){
                neighbors.push_back(*iter+1);
                //if(neighbors_dists != NULL)
                    neighbors_dists.push_back(curr_Dist);
            }

            // Found m neighbors 
            if(neighbors_num == this->threshold)
                break;
        } 
        // end for - Found m neighbors 
        if(neighbors_num == this->threshold)
            break;
    } // end for - Probes
}

void Hypercube::nNeighbor(vector<int> query, int N, vector<pair<long double, int>>& near_items){
    int i ,cube_id,pos;
    double curr_Dist; // Distance of a point in list
    vector<Neighbor_Vertice> Neighbor_Vertices; // Keep all neighbors  
    int neighbors_num = 0; // Number of neighbors

	// Find initial vertice 
	cube_id = hypercube_hash(query);

    // Find all neighbors of that vertice 
	for(i = 0; i < this->buckets_num; i++){

		// Don't check the same position 
		if(i == cube_id)
			continue;
			
			Neighbor_Vertices.push_back(Neighbor_Vertice(hammingDistance(cube_id, i), i));
	}

    // Sort Neighbor Vertices 
	make_heap(Neighbor_Vertices.begin(), Neighbor_Vertices.end(), Compare_Vertices());
	sort_heap(Neighbor_Vertices.begin(), Neighbor_Vertices.end(), Compare_Vertices());

	// for(i = 0; i < this->buckets_num; i++){
	// 	 	std::cout << Neighbor_Vertices[i].id << " ";
	// }

	long double min = 4294967291;
    // Check probes vertices for neighbors 
	for(i = 0; i < this->max_probes; i++){
	
		// Check initial pos 
		if(i == 0)
			pos = cube_id;
		// Extract minimum position
		else
			pos = Neighbor_Vertices[i-1].id;
		
		// Empty vertice 
		if(this->hypercube[pos].size() == 0)
			continue;

		bool var = false;
        // Scan current vertice 
		for(auto iter = this->hypercube[pos].begin(); iter != this->hypercube[pos].end(); iter++){  
				
			neighbors_num += 1;	
			// Find current distance 
			curr_Dist = euclidean_dis(data_vectors.at(*iter),query);
				
			if(curr_Dist < min){
               	
				min = curr_Dist;
				//cout << *iter << "\n";
				for(auto j = near_items.begin();j!=near_items.end();j++){
					if(j->second == *iter+1){
						var=true;
						break;
					}
				}
				
				if(var!=true)
				{
					if (near_items.size() >= N) {
						near_items.pop_back();
					}

					near_items.push_back(make_pair(curr_Dist, *iter+1));
					sort(near_items.begin(), near_items.end(),[](pair<long double, int> const& a, pair<long double, int> const& b)
					{
						return a.first < b.first;
					});
					min = near_items.back().first;
				}
				var=false;
			}

            // Found threshhold neighbors 
            if(neighbors_num ==this->threshold)
                break;
        } // End for ~ Scan list

        // Found threshhold neighbors 
        if(neighbors_num == this->threshold)
            break;
    } // End for ~ Probes
}