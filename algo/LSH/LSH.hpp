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

#include "../Handling_input/Handling_input.hpp"

using namespace std;

static vector<vector <double>> v; /* Vectors with random normal numbers, used for hashfunction */

static vector<vector <int>> Hash_Functions;

// #Points
static long int n;

// #Dimensions
// #Numbers in a vector of an item
static int dimension;

static int w;

// Vector with random numbers between 0 and w picked uniformly
static vector<double> t;

double Normal_distribution(); /* Generates a sequence of random normal numbers */

void Initialize_Hash_parameters(); /* Initialize the variables used by the hash function */

void Euclidean_Hash_Function(int L, int k); /* Here we initialize all vectors */

void Calculate_Hash_Value(int L, int k, int item);