#include "./Handling_input/Handling_input_cube.hpp"
#include "./LSH/hypercube.hpp"

class Hypercube;
using namespace std;
Hypercube *Hpb;

// ./cube -i ./files/input_small_id -q ./files/query_small_id -o output_file

int main(int argc, char *argv[]) {

    store_data(argc, argv);

    read_file(Hpb->query_data, Hpb->query_file);

    int queries = Hpb->query_data.size();
    
    ofstream Output;
    Output.open (Hpb->output_file, ofstream::out | ofstream::trunc);

    vector<pair<long double, int>> ANN_result;
    vector<double>                 NNB_result;

    for (int query = 0; query < queries; query++) {
        Output << "Query:" << query << endl;
        auto begin = high_resolution_clock::now();
        Hpb->nNeighbor(Hpb->query_data[query], Hpb->N, ANN_result);
        auto end = high_resolution_clock::now();
        Hpb->ANN_time = end - begin;

        begin = high_resolution_clock::now();
        NNB_result = Nearest_N_brute(Hpb->get_data(), Hpb->query_data[query], Hpb->N);
        end = high_resolution_clock::now();
        Hpb->NNB_time = end - begin;

        list<int> neighbors;
        list<double> neighbors_dists;
        Hpb->RNeighbors(Hpb->query_data[query],Hpb->R,neighbors, neighbors_dists);
        // neighbors_dists.sort();

        for (int neighbor = 0; neighbor < Hpb->N; neighbor++) {
            Output << "Nearest neighbor-" << neighbor << ": ";
            neighbor > ANN_result.size() - 1 ?
                Output << "Not Found" << endl << "distanceHypercube: " << endl:
                Output << ANN_result[neighbor].second << endl
                << "distanceHypercube: " << ANN_result[neighbor].first << endl;
            Output << "distanceTrue: " << NNB_result[neighbor] << endl << endl;
        }

        Output << "tLSH: " << Hpb->ANN_time.count() << endl;
        Output << "tTrue: " << Hpb->NNB_time.count() << endl << endl;

        Output << "R-near neighbors:" << endl;
        for (auto point: neighbors) {
            Output << point << endl;
        }
        Output << endl;
    }
    
    Output.close();

    // Print_values();
}