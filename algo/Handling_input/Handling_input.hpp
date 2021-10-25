#ifndef HANDLING_INPUT_HPP
#define HANDLING_INPUT_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

long int dim_data(); /* Get the dimensions of the data */

long int num_of_points(); /* Get the number of the items */

void read_file(vector<vector<int>> &,string );
vector<vector<int>> store_data(int, char**);
bool string_operation(char ** str,char *str2,string& str3,int i);
bool number_operation(char ** str,char *str2,int num,int i);

#endif