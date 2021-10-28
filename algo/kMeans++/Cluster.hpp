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
#include <time.h>
#include <algorithm>
#include <chrono>

#include "./Handling_input/Handling_input.hpp"

class Cluster {
    private:
        int L=3; // num of hash tables for LSH
        int k=4; // k of LSH
        int number_of_clusters;
        int max_number_M_hypercube = 10;
        int number_of_hypercube_dimensions = 3;
        int number_of_probes = 2;
        string input_file, config_file, output_file;
    public:
        vector<vector<int>> data; // Input data

        Cluster(string, string, string);
        ~Cluster();

        void read_config(string );

        void print() {
            cout << "number_of_clusters: " << number_of_clusters << endl;
            cout << "number_of_vector_hash_tables: " << L << endl;
            cout << "number_of_vector_hash_functions: " << k << endl;
            cout << "max_number_M_hypercube: " << max_number_M_hypercube << endl;
            cout << "number_of_hypercube_dimensions: " << number_of_hypercube_dimensions << endl;
            cout << "number_of_probes: " << number_of_probes << endl;
        }
};

#endif