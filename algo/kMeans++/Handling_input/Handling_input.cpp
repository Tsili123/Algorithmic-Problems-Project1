#include "../Cluster.hpp"

using namespace std;

extern Cluster *cluster;

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

vector<vector<int>> store_Cluster_data(int argc,char** argv){
    string input_file = "", configuration_file = "", output_file = "";
    int N = 1, R = 10000, k = 4, L = 5;
    string Method;
    bool complete = false;

    if(argc < 9 || argc > 10){
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
        else if (!strcmp(argv[i], "-c")) {
            i++;
            configuration_file = string(argv[i]);
        }
        else if (!strcmp(argv[i], "-o")) {
            i++;
            output_file = string(argv[i]);
        }
        else if(strcmp(argv[i], "-complete")==0){
            complete = true;
        }
        else if(strcmp(argv[i], "-m")==0){
            complete = true;
            i++;
            Method = string(argv[i]);
        }
    }

    if (input_file == "" || configuration_file == "" || output_file == "") {
        cout << "Error: Missing files directory" << endl;
        exit (EXIT_FAILURE);
    }
        
    vector<vector<int>> vec;
    read_file(vec,input_file);

    cluster = new Cluster(input_file, configuration_file, output_file, complete, Method);

    return vec;
}