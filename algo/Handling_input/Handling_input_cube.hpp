#ifndef HANDLING_INPUT_CUBE_HPP
#define HANDLING_INPUT_CUBE_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

long int dim_data(); /* Get the dimensions of the data */

long int num_of_points(); /* Get the number of the items */

void read_file(vector<vector<int>> &,string );
void store_data(int a, char** b);
bool string_operation(char ** str,char *str2,string& str3,int i);
bool number_operation(char ** str,char *str2,int num,int i);

#endif