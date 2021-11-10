#ifndef LLOYD_H
#define LLOYD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <iomanip>
#include <cmath>
#include <map>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <time.h>
#include <algorithm>
#include <chrono>

#include "./Handling_input/Handling_input.hpp"
// #include "../Handling_input/Handling_input_cube.hpp"
#include "../Handling_input/Handling_input.hpp"
#include "../LSH/LSH.hpp"
#include "../LSH/hypercube.hpp"
#define NUM 1.79769e+308 // Biggest double num that can be defined

using std::chrono::high_resolution_clock;
using std::chrono::duration;


class Cluster {
    private:
        bool complete = false;
        string Method;
        int L=3; // num of hash tables for LSH
        int k=4; // k of LSH
        int num_of_Items;
        int number_of_clusters;
        int max_number_M_hypercube = 10;
        int number_of_hypercube_dimensions = 3;
        int number_of_probes = 2;
        string input_file, config_file, output_file;

        duration<double> Cluster_time;
        // The centroids kMeans++ initialized
        vector<int> centroids;
        // Silhouette results
        vector<long double> s;
        // The first vector is the centroid and the second is a vector of indexes
        vector<pair<vector<int>, vector<int>>> Lloyd;

		// vector that hols the index of the centroid that the current index's vector is assigned to
		vector<int> assigned_centroid;

        vector<pair<vector<int>, vector<int>>> reverse_centroids;

		// in case of lsh, we need these extra variables
		//LSH* lsh_ptr;

		// in case of hypercube, we need these extra variables
		Hypercube* hypercube_ptr;
        //---------

    public:
        vector<vector<int>> data; // Input data

        Cluster(string, string, string, bool, string);
        ~Cluster();

        void kMeanspp_Initialization();
        void Lloyd_method();
        vector<int> Calculate_Mean(vector<int>);
        bool Compare(vector<vector<int>>);
        void Silhouette();
        string get_method(void){return Method;};
        void read_config(string );

        void output();
        void print();

        int unassigned_count();
        int nearest_centroid(vector<int> vec);
        long int  min_distance_between_centroids(void);
        int reverse_assignment(void);
};

long double euclidean_dis(vector<int> vec1, vector<int> vec2);

#endif