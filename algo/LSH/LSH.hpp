#ifndef LSH_H
#define LSH_H

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

#define M 4294967291

#include "../Handling_input/Handling_input.hpp"

using namespace std;

class Bucket
{
    public:
        vector<pair<pair<long long int, long long int>, long int>> points;     

        void add(long long int, long int, long long int);

};

class LSH{
    private:
        int k; /* #LSH Functions */
        int L; /* #Hash Tables  */
        // #Points
        long long int points_num;

        // #Dimensions
        // #Numbers in a vector of an item
        int dimension;
        int w;

        int queries_num,R,N,m;
        long int hashtable_size;
        Bucket*** hashtables;
        // int* modulars;
        // double *tLSH,*tTrue,dist_AF,time_error;
        // int **s_i,**True_Distances;
        fstream file;
    public:
        string input_file, query_file, output_file;
        vector<vector<int>> data; // Input Data
        vector<vector<int>> queries_data; // Input Data

        LSH(string, string, string, int L_, int N_, int k_, int R_, long long int n, int dim);
        ~LSH();
        int get_queriesnum() { return queries_num; }
        int get_pointsnum() { return points_num; }
        long int get_hashtablesize() { return hashtable_size; }
        int get_w() { return w; }
        int get_L() { return L; }
        int get_k() { return k; }
        int get_N() { return N; }
        int get_R() { return R; }
        int get_dimension() { return dimension; }
        Bucket*** get_hashtables(){ return hashtables; }
        void set_w(int value) { w = value; }

        vector<long long int> Specific_Hash_Value(int g, vector<int> item);

        void print_buckets();
};

void LSH_Insert_Points_To_Buckets(LSH* info);

static vector<vector <double>> v; /* Vectors with random normal numbers, used for hashfunction */

static vector<vector <int>> Hash_Functions;

// Vector with random numbers between 0 and w picked uniformly
static vector<double> t;

double Normal_distribution(); /* Generates a sequence of random normal numbers */

void Euclidean_Hash_Function(int L, int k); /* Here we initialize all vectors */

void Calculate_Hash_Value(int L, int k, vector<int> item);

long long int mod(long long int, long int);

void Print_values(); /* Used for Debugging */

long double euclidean_dis(vector<int> , vector<int> );

int Nearest_N_brute(vector<int> );

vector<int> Brute_by_range(vector<int> );

vector<int> Nearest_N_search(vector<int> );

vector<int> Search_by_range(vector<int> );

#endif