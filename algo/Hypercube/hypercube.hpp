#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cctype>
#include <ctime>
#include <utility>
#include <list>
#include <chrono>
#include <string>
#include <random>
#include <algorithm> // for heap 

#include "../functions/functions.hpp"

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

typedef std::vector<std::list<int>> hypercube_hashtable;

class Euclidean_H_i {
    private:

        std::vector<std::vector<double>> v; /* Vectors with random normal numbers, used for hashfunction */
        std::vector<double> t; // Vector with random numbers between 0 and w picked uniformly  
		int w ;
		int k;
		int dimlim;
    public:

        Euclidean_H_i(int k_, int dimlim_, long double W){
			dimlim = dimlim_;
			k=k_;
			// Initialize the vectors used for hashing
			v.resize(k, std::vector<double>(dimlim));

			for(int i=0; i < k; i++) {
				v[i].clear();

				for(int j=0; j < dimlim; j++){
					v[i].push_back(Normal_distribution());
				}
			}

			// Initialize w (change it to your liking)
			w = W;

			srand(time(0));

			// Initialize vector t
			// Inspired from https://en.cppreference.com/w/cpp/numeric/random/uniform_real_distribution
			t.clear();

			std::random_device generator;
			std::uniform_real_distribution<float> dis(0.0, (float) w);

			for(int i=0; i<k; i++){ 	// For every hash function
				float random = dis(generator);
				t.push_back(random);
			}

		}

        ~Euclidean_H_i(){
    		v.clear();
    		t.clear();
		} 
		
		int Specific_Hi(std::vector<int> item,int var) {
			long int sum = 0;
			for (int var2 = 1; var2 < dimlim; var2++) {
        		sum += item[var2] * v[var][var2];
    		}
			sum += t[var];
    		sum = floor(sum /(double) w);
			return sum;
		}
		
        std::vector<std::vector <double>> get_vector_v() { return v; }
        std::vector<double> get_vector_t() { return t; }
};

class Hypercube{
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
            bool operator()(const Neighbor_Vertice& x, const Neighbor_Vertice& y) const{
                return x.hamming_distance < y.hamming_distance;
            }
        };


    int k; // number of hash functions , meaning the size of hypercube
	int threshold; // max elements to be checked during the program
    int buckets_num; // number of buckets in the hash table
    int points_num; // number of points to be hashed
    int w; // a number signifficantly larger thar the radius, affects range search
    int space; // the dimension of the space we are going to have
	int max_probes; // max probes of the hypercube to be checked during search

    // Hypercube is a hashtable
	hypercube_hashtable hypercube;
	Euclidean_H_i *H_i_ptr;
	// vector of the vectors is given 
	std::vector<std::vector<int>> data_vectors; 
	std::vector<std::uniform_int_distribution<int> > f_i; // Distributions for fi 
	std::default_random_engine generator; 
    std::vector<std::unordered_map<int, bool>  > Hi_map; //  map f with unique values
	// generator and the random distribution for the mapping
	public:
		int N;
		int R;
		std::string input_file;
		std::string query_file;
		std::string output_file;
		std::vector<std::vector<int>> query_data;
		duration<double, std::milli> ANN_time;
        duration<double, std::milli> NNB_time;

		Hypercube(std::string input_, std::string query_, std::string output_,int R_,int k_,int threshold_, 
		int points_num_,int N_,int space_,int max_probes_,std::vector<std::vector<int>> data_vectors_);

		~Hypercube();

		int hypercube_hash(std::vector<int> vec_point);

		// Function to calculate hamming distance
		int hammingDistance(int n1, int n2);
	
		void RNeighbors(std::vector<int> query, int radius, std::list<int>& neighbors, std::list<double>& neighbors_dists);

		/* Find theN nearest neighbors of a given point */
		void nNeighbor(vector<int> query, int N, vector<pair<long double, int>>& near_items);

		vector<std::vector<int>> get_data() { return this->data_vectors; }
};

		
		
		