#include "../LSH/LSH.hpp"
#include "../kMeans++/Cluster.hpp"

using namespace std;

string dir_input = "";

extern LSH *Lsh; /* LSH Object */

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

//g++ -c -o main.o main.cpp
//g++ -o lsh main.o
// ./lsh -i input_small_id -q query_file -k 4 -L 5 -o output -N 1 -R 1000
// ./lsh -i input_small_id -q query_file -k 4 -L 5 -o output -N 1 -R 1000
void read_file(vector<vector<int>> &vec,string input_file){
    string line;
    if (dir_input == "") dir_input = input_file;
    ifstream Data_File(input_file);
    
    if (Data_File.is_open()){
        int rows = 0;
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
            //cout << columns;
            rows++;
        }
        
    }else cout << "Unable to open file"; 
    Data_File.close();
    
}

void store_LSH_data(int argc,char** argv){
    string input_file = "", query_file = "", output_file = "";
    int N = 1, R = 10000, k = 4, L = 5;

    if(argc < 7 || argc > 15){
        cout << "Error in command line arguments:" << endl;
        cout << "argc " << argc << endl;
        cout << "Program exiting due to error ..." << endl;
        exit (EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-i")) {
            i++;
            input_file = string(argv[i]);
        }
        else if (!strcmp(argv[i], "-q")) {
            i++;
            query_file = string(argv[i]);
        }
        else if (!strcmp(argv[i], "-o")) {
            i++;
            output_file = string(argv[i]);
        }
        else if (!strcmp(argv[i], "-k")) {
            i++;
            k = atoi(argv[i]);
        }
        else if (!strcmp(argv[i], "-L")) {
            i++;
            L = atoi(argv[i]);
        }
        else if (!strcmp(argv[i], "-N")) {
            i++;
            N = atoi(argv[i]);
        }
        else if (!strcmp(argv[i], "-R")) {
            i++;
            R = atoi(argv[i]);
        }
    }

    if (input_file == "" || query_file == "" || output_file == "") {
        cout << "Error: Missing files directory" << endl;
        exit (EXIT_FAILURE);
    }

    vector<vector<int>> vec;
    read_file(vec,input_file);

    Lsh = new LSH(input_file, query_file, output_file, L, N, k, R, num_of_points(), dim_data(), vec);
}