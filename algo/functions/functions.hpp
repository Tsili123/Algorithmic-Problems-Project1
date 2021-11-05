#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <random>

#define BIG 4294967291

using namespace std;

double Normal_distribution(); /* Generates a sequence of random normal numbers */

vector <double> Nearest_N_brute(vector<vector<int>>, vector<int> , int);

long double euclidean_dis(vector<int> , vector<int> ); /* Calculate Euclidean Distance */