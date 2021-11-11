#ifndef HANDLING_INPUT_HPP
#define HANDLING_INPUT_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std;

void store_LSH_data(int, char**);
vector<vector<int>> store_Cluster_data(int, char**);
bool string_operation(char ** str,char *str2,string& str3,int i);
bool number_operation(char ** str,char *str2,int num,int i);

#endif