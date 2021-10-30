#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <ctime>
#include <utility>
#include <list>
#include <string>

typedef std::vector<std::list<int>> hypercube_hashtable;
Euclidean_H_i *H_i_ptr;

template <typename T>

class Euclidean_H_i {
    private:
        vector<vector <double>> v; /* Vectors with random normal numbers, used for hashfunction */
        vector<double> t; // Vector with random numbers between 0 and w picked uniformly  
		int w ;
		long int *h_i;
		int k;
    public:
        Euclidean_H_i_init(int k, int dimlim) {

			h_i = new long int[k];
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

		Specific_H_i(vector<int> item) {
			long int sum;
			for (int var = 1; var < k; var++) {
				for (int var2 = 1; var2 < dimlim; var2++) {
            		sum += item[var2] * v[var2];
        		}
				sum += t[var];
        		sum = floor(sum /w);
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
    //hash functions for every point in the hypercube
	LSH::Euclidean_Hash_Function hash_funcs;
	// vector of the vectors is given 
	std::vector<std::vector<int>> data_vectors;   
	// mapping the fliped-coins decision for every possible outcoume of the hash function
	std::vector<std::unordered_map<int, bool>> flipped_coins;

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
            Euclidean_H_i::Euclidean_Hi(k,space);

            // initialize the hypercube hashtable
            //every bucket contains a list of integers
            //each one integers means the id of the point at the data
            // for example : the number 2 means the second point etc ..
            for (int i = 0; i < buckets_num; i++) {
                std::list<int> temp_list;
                hypercube.push_back(temp_list);
            }
			
			// create the list of the f_i functions
			for (int i = 0; i < k; i++) {
				std::unordered_map<int,bool> current_map;
				// compute all the possible hash function outcomes to 0-1, so we save time 
				for (int j = 0; j < buckets_num; j++) {
					bool res = dist(gen);
					current_map.insert({i, res});
				}
				flipped_coins.push_back(current_map);
			}

			// insert all of the points into the hypercube
			for (int i = 0; i < points_num; i++) {
				int bucket_id = hypercube_hash(data_vectors.at(i));
				hypercube[bucket_id].push_back(i);
			}

			// hypercube initialization done. print the time differenct

			time(&finish);
			cout << " Hypercube created in " << difftime(finish, start) << " sec" << endl;
		}

		~Hypercube(){};

		int hypercube_hash(std::vector<int> vec_point){
			// store the string produced
			std::string bucket_str;
			// hash k times
			for(int i=0;i<this->k;i++){
                    // hash with the i-th hash fn
					H_i_ptr->Specific_H_i(vec_point);
                    long int res = H_i_ptr->get_h_i(k);
					res = res % bucket_num;
					// find its pre-maped result of a coin flip
					bool bit = flipped_coins[i][res];
					// append the 0/1 value to the string
					bucket_string += std::to_string(bit);
			    }
            }
			

			// convert the bitstring into an integer
			return (int)std::bitset<32>(bucket_string).to_ulong();
		}

		
		
		
		