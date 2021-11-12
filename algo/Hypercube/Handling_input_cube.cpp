#include "./Handling_input_cube.hpp"
#include "./hypercube.hpp"

using namespace std;
extern Hypercube *Hpb;

void store_data(int argc,char** argv){
    string input_file = "", query_file = "", output_file = "";
    int N = 1, R = 10000, k = 14, probes = 2, M = 10;

    if(argc < 7 || argc > 17){
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
        else if (!strcmp(argv[i], "-probes")) {
            i++;
            probes = atoi(argv[i]);
        }
        else if (!strcmp(argv[i], "-N")) {
            i++;
            N = atoi(argv[i]);
        }
        else if (!strcmp(argv[i], "-R")) {
            i++;
            R = atoi(argv[i]);
        }
        else if (!strcmp(argv[i], "-M")) {
            i++;
            M = atoi(argv[i]);
        }
    }

    if (input_file == "" || query_file == "" || output_file == "") {
        cout << "Error: Missing files directory" << endl;
        exit (EXIT_FAILURE);
    }
    //data vector
    vector<vector<int>> vec;
    read_file(vec,input_file);

    Hpb = new Hypercube(input_file,query_file, output_file, R,k,1000,num_of_points(),N, dim_data(),probes,vec);
}