#include "./Cluster.hpp"

using namespace std;

extern Cluster *cluster;

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