#include "../LSH_File/LSH.hpp"
#include "../kMeans++/Cluster.hpp"

using namespace std;

extern LSH *Lsh; /* LSH Object */

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