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

//Forward declaration
class Bucket;

class LSH{
    private:
        int k; /* #LSH Functions */
        int L; /* #Hash Tables  */
        int points_num,queries_num,R,dimension,W,N,m,HashTableSize;
        // int* modulars;
        // double *tLSH,*tTrue,dist_AF,time_error;
        // int **s_i,**True_Distances;
        int **points_array,**queries_Array;
        Bucket*** hashtables;
        string input_file,query_file,output_file;
        fstream file;
    public:
        LSH(string, string, string, int L_,int N_,int k_,int R_);
        ~LSH();
        Bucket*** get_HashTables();
        int** get_QueriesArray();
        int** get_PointsArray();
        int get_QueriesNum() { return queries_num; }
        int get_PointsNum() { return points_num; }
        int get_HashTableSize() { return HashTableSize; }
        int get_W() { return W; }
        int get_L() { return L; }
        int get_k() { return k; }
        int get_N() { return N; }
        // int get_M() { return M; }
        int get_dimension() { return dimension; }
};

static vector<vector <double>> v; /* Vectors with random normal numbers, used for hashfunction */

static vector<vector <int>> Hash_Functions;

// #Points
static long long int n;

// #Dimensions
// #Numbers in a vector of an item
static int dimension;

static int w;

// Vector with random numbers between 0 and w picked uniformly
static vector<double> t;

double Normal_distribution(); /* Generates a sequence of random normal numbers */

void Initialize_Hash_parameters(); /* Initialize the variables used by the hash function */

void Euclidean_Hash_Function(int L, int k); /* Here we initialize all vectors */

void Calculate_Hash_Value(int L, int k, vector<int> item);

long long int mod(long long int);

void Print_values(); /* Used for Debugging */

long long int euclidean_dis(vector<int> , vector<int> );

#endif