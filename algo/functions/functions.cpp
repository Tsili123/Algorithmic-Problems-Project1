#include <iostream>

#include "functions.hpp"

using namespace std;

string dir_input = "";

// The dimension of the Data is the #integers an item has
long int dim_data() {
    long int dim = 0;

	string str;

    ifstream Data_File(dir_input); /* Data File */

	getline(Data_File, str);

    dim = std::count(str.begin(), str.end(), ' ');

	Data_File.clear();
	Data_File.seekg(0,ios::beg); // Reseting the pointer
    Data_File.close();

	return dim;
}

long int num_of_points() {

	long int num_of_lines = 0;

	string str;

    ifstream Data_File(dir_input); /* Data File */

	while(getline(Data_File, str)) ++num_of_lines;

	Data_File.clear();
	Data_File.seekg(0,ios::beg); // Reseting the pointer
    Data_File.close();

	return num_of_lines;
}

void read_file(vector<vector<int>> &vec, string input_file){
    string line;
    if (dir_input == "") dir_input = input_file;
    ifstream Data_File(input_file);
    
    if (Data_File.is_open()){
        while(getline(Data_File,line)){
            stringstream s;
            s << line;                   //send the line to the stringstream object

            int columns = 0;    
            double d;
            vector<int> v1;

            while(s >> d){
                int num = static_cast<int>(d);
                v1.push_back(num);
                columns++;  //while there's something in the line, increase the number of columns
            } 
            vec.push_back(v1);

            v1.clear();
            s.str("");
        }
        
    }else cout << "Unable to open file"; 
    Data_File.close();
}

double Normal_distribution() {
    // Inspired from https://en.cppreference.com/w/cpp/numeric/random/normal_distribution
    random_device rd{};
    mt19937 gen{rd()};
 
    normal_distribution<float> d{0, 1};
 
    map<int, int> hist{};
    return round(d(gen));
}

// Calculate Euclidean Distance
long double euclidean_dis(vector<int> vec1, vector<int> vec2) {
    long double dist=0.0;

    auto itA = vec1.begin();
    auto itB = vec2.begin();
    ++itA;
    ++itB;

    while(itA != vec1.end() || itB != vec2.end())
    {
        dist = dist + (itA[0]-itB[0])*(itA[0]-itB[0]);
        if(itA != vec1.end()) {
            ++itA;
        }
        if(itB != vec2.end()) {
            ++itB;
        }
    }

	return sqrt(dist);
}

vector <double> Nearest_N_brute(vector<vector<int>> data, vector<int> query, int N) {
    long double d = (double) BIG; // Minimum distance

    vector <double> near_items;

    for (auto Item: data) {
        long double euc_dist = euclidean_dis(Item, query);

        if (euc_dist < d) {
            if (near_items.size() >= N) {
                near_items.pop_back();
            }
            near_items.push_back(euc_dist);
            sort(near_items.begin(), near_items.end());
            d = near_items.back();
        }
    }

    return near_items;
}