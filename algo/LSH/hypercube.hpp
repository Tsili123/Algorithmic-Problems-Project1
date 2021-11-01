#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <utility>
#include <list>
#include <string>

typedef std::vector<std::list<int>> hypercube_hashtable;

template <typename T>

class Euclidean_H_i {
    private:

		// For every vertice find all neighbors and scan up to probes vertices(sorted by hamming Distance)  with min heap
        typedef struct Neighbor_Vertice{
            int hamming_distance; // Hamming distance with current id
            int id; // id in  hypercube_hashtable 
        
            Neighbor_Vertice(int dist, int id){
                this->hamming_distance = dist;
                this->id = id;
            }
        }Neighbor_vertice;

        //  Compare class based for hamming distance
        struct Compare_Vertices{
            bool operator()(const neighbor_Vertice& x, const neighbor_Vertice& y) const{
                return x.hamming_distance > y.hamming_distance;
            }
        };

        vector<vector <double>> v; /* Vectors with random normal numbers, used for hashfunction */
        vector<double> t; // Vector with random numbers between 0 and w picked uniformly  
		int w ;
		int k;
    public:
        Euclidean_H_i_init(int k_, int dimlim) {

			k=k_;
			// Initialize the vectors used for hashing
			v.resize(k, vector<double>(dimlim));

			for(int i=0; i < k; i++) {
				v[i].clear();

				for(int j=0; j < dimlim; j++){
					v[i].push_back(Normal_distribution());
				}
			}

			// Initialize w (change it to your liking)
			w = 500;

			srand(time(0));

			// Initialize vector t
			// Inspired from https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
			t.clear();

			random_device generator;
			uniform_real_distribution<float> dis(0.0, (float) w);

			for(int i=0; i<k; i++){ 	// For every hash function
				float random = dis(generator);
				t.push_back(random);
			}

		}

        ~Euclidean_Hash_Function(){
    		v.clear();
    		t.clear();
		} 

		Specific_Hi(vector<int> item) {
			long int sum;
			for (int var = 1; var < k; var++) {
				for (int var2 = 1; var2 < dimlim; var2++) {
            		sum += item[var2] * v[var][var2];
        		}
				sum += t[var];
        		sum = floor(sum /(double) w);
				h[var] = sum;
				sum=0;
			}
		}
		
        vector<vector <double>> get_vector_v() { return v; }
        vector<double> get_vector_t() { return t; }
		long int get_h_i(int pos){return h_i[pos];}
};

class Hypercube{
	private:
    
	long long int m; // Constant for hash function.Typically 2^32 - 5
    int k; // number of hash functions , meaning the size of hypercube
	int threshold; // max elements to be checked during the program
    int buckets_num; // number of buckets in the hash table
    int points_num; // number of points to be hashed
    int w; // a number signifficantly larger thar the radius, affects range search
    int space; // the dimension of the space we are going to have
	int max_probes; // max probes of the hypercube to be checked during search

    // Hypercube is a hashtable
	hypercube_hashtable hypercube;
	Euclidean_H_i *Hi_ptr;
	// vector of the vectors is given 
	std::vector<std::vector<int>> data_vectors; 
	
	std::vector<std::uniform_int_distribution<int> > f_i; // Distributions for fi 
	std::default_random_engine generator; 
    std::vector<std::unordered_map<int, bool>  > Hi_map; //  map f with unique values

	public:
    
        //Constructor class
		Hypercube(long long int m_,int k_,int threshold_, 
		int points_num_,int w_,int space_,int max_probes_,std::vector<std::vector<int>> data_vectors_) : 
		m(m_),k(k_), threshold(threshold_), points_num(points_num_),w(w)_,space(space_),max_probes(max_probes_),data_vectors(data_vectors_) {
			
            //measure the time that it takes to initialize the hypercube
            time_t start, finish;
            fprintf(stdout, "Hypercube program with parameters: m = %d, k = %ld, threshold = %d
            points_num = %d, w = %d, space = %d, max_probes = %d,\n", k, m, threshold, points_num, w, space, max_probes);
            
            time(&start);
            
            // generator and the random distribution for the mapping
			std::random_device rd;
			std::default_random_engine gen(rd());
			std::uniform_int_distribution<int> dist(0,1);

            // we have a bitstring of k bits, thus the size of the hypercube table will be 2^k
            buckets_num = (int)pow(2, k);

            //Create hash functions for each bucket
            H_i_ptr = new Euclidean_H_i_Init(k,space);

            // initialize the hypercube hashtable
            //every bucket contains a list of integers
            //each one integers means the id of the point at the data
            // for example : the number 2 means the second point etc ..
            for (int i = 0; i < buckets_num; i++) {
                std::list<int> temp_list;
                hypercube.push_back(temp_list);
            }
			

			// insert all of the points into the hypercube
			for (int i = 0; i < points_num; i++) {
				int bucket_id = hypercube_hash(data_vectors.at(i));
				this->hypercube[bucket_id].push_back(i);
			}

			// hypercube initialization done. print the time differenct

			time(&finish);
			cout << " Hypercube created in " << difftime(finish, start) << " sec" << endl;
		}

		~Hypercube(){};

		int hypercube_hash(std::vector<int> vec_point){
			// store the string produced
			std::string bucket_string = "";
			int curr_Hi;
			bool curr_Fi;
			unordered_map<int, bool>::const_iterator iterh; // Iterate through map

			// hash k times
			for(int i=0;i<this->k;i++){
                    // hash with the i-th hash fn
					curr_Hi = this->Hi_ptr->Specific_Hi(vec_point);

					// Find if H[i] value exists 
        			iterh = this->Hi_map[i].find(curr_Hi);

					// Exists 
        			if(iterh != this->Hi_map[i].end())
            			curr_Fi = iterh->second;
					// Map current H[i] and add it in the map 
        			else{
            			curr_Fi = this->f_i[i](this->generator);
            			this->Hi_map[i].insert(pair<int, bool>(curr_Hi, curr_Fi));
        			}
					bucket_string += std::to_string(curr_Fi);
		    }

			// convert the bitstring into an integer
			return stoi(bucket_string, nullptr, 2);
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

	// Function to calculate hamming distance
	int hammingDistance(int n1, int n2)
	{
		int x = n1 ^ n2;
		int setBits = 0;
	
		while (x > 0) {
			setBits += x & 1;
			x >>= 1;
		}
	
		return setBits;
	}
 

	void RNeighbors(vector<int> query, int radius, list<vector<int>>& neighbors, list<double>* neighbors_dists){ 
		int i, cube_id, pos;
		double currDist; // Distance of a point in list
		vector<Neighbor_Vertice> Neighbor_Vertices; // Keep all neighbors  
		int neighbors_num = 0; 
		
		// Clear given lists 
		neighbors.clear();
		if(neighbors_dists != NULL)
			neighbors_dists->clear();

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

		// Check probes vertices for neighbors 
		for(i = 0; i < this->max_probes; i++){
	
			// Check initial pos 
			if(i == 0)
				pos = cube_id
			// Extract minimum position
			else
				pos = Neighbor_Vertices.front().id;

			// Empty vertice 
			if(this-> hypercube_hashtable[pos].size() == 0)
				continue;

			// Scan current vertice 
			for(auto iter = this-> hypercube_hashtable[pos].begin(); iter != this-> hypercube_hashtable[pos].end(); iter++){  

				neighbors_num += 1;
				
				// Find current distance 
				curr_Dist = euclidean_dis(data_vectors.at(*iter),query);
				
				// Keep neighbor 
				if(curr_Dist < radius){
					neighbors.push_back(*iter);
					if(neighbors_dists != NULL)
						neighbors_distances->push_back(curr_Dist);
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

		
		
		