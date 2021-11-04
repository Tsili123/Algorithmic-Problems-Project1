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

bool string_operation(char ** str,char *str2,string &str3,int i){
    if(strcmp(str[i],str2)==0){
            str3 = string(str[i+1]);
            return true;
    }
    else{//error case
        cout << "Error in command line arguments:" << endl;
        cout << "Expected " << string(str2) << " but you typed " << string(str[i]) << endl;
        return false;
    }
}

bool number_operation(char ** str,char *str2,int *num,int i){
    if(strcmp(str[i],str2)==0){
            *num = atoi(str[i+1]);
            return true;
    }
    else{
        //error case
        cout << "Error in command line arguments:" << endl;
        cout << "Expected " << string(str2) << " but you typed " << string(str[i]) << endl;
        return false;
    }
}

vector<vector<int>> store_Cluster_data(int argc,char** argv){
    string input_file, configuration_file, output_file;
    string Method;
    bool complete = false;

    if(argc!=9 && argc != 10){
        cout << "Error in command line arguments:" << endl;
        cout << "Program exiting due to error ..." << endl;
        return {};
    }

    int i=1;
    
    if(string_operation(argv, (char*) "-i", input_file,i) == false){
        cout << "Program exiting due to error ..." << endl;
        return {};
    }

    i=i+2;

    if(string_operation(argv, (char*) "-c", configuration_file,i) == false){
        cout << "Program exiting due to error ..." << endl;
        return {};
    }

    i=i+2;
    if(string_operation(argv, (char*) "-o",output_file,i) == false){
        cout << "Program exiting due to error ..." << endl;
        return {};
    }

    i=i+2;
    if (argc == 10) {
         if(strcmp(argv[i],(char*) "-complete")==0){
            complete = true;
        }
        else{//error case
            cout << "Error in command line arguments:" << endl;
            cout << "Expected -complete but you typed " << argv[i] << endl;
            cout << "Program exiting due to error ..." << endl;
            return {};
        }
        i++;
    }

    if(string_operation(argv, (char*) "-m", Method,i) == false){
        cout << "Program exiting due to error ..." << endl;
        return {};
    }
        
    vector<vector<int>> vec;
    read_file(vec,input_file);

    cluster = new Cluster(input_file, configuration_file, output_file, complete, Method);

    return vec;
}