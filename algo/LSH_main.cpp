#include "./LSH/bucket.hpp"

using namespace std;

LSH *Lsh;

int main(int argc, char *argv[]) {

    store_LSH_data(argc, argv);

    read_file(Lsh->queries_data, Lsh->query_file);

    LSH_Insert_Points_To_Buckets(Lsh);

    int queries = Lsh->queries_data.size();
    int N = Lsh->get_N();

    ofstream Output;
    Output.open (Lsh->output_file, ofstream::out | ofstream::trunc);

    vector<pair<long double, int>> ANN_result;
    vector<double>                 NNB_result;
    vector<int>                    SBR_result;

    for (int query = 0; query < queries; query++) {
        Output << "Query:" << query << endl;
        auto begin = high_resolution_clock::now();
        ANN_result = Nearest_N_search(Lsh->queries_data[query]);
        auto end = high_resolution_clock::now();
        Lsh->ANN_time = end - begin;

        begin = high_resolution_clock::now();
        NNB_result = Nearest_N_brute(Lsh->queries_data[query]);
        end = high_resolution_clock::now();
        Lsh->NNB_time = end - begin;

        SBR_result = Search_by_range(Lsh->queries_data[query]);

        for (int neighbor = 0; neighbor < N; neighbor++) {
            Output << "Nearest neighbor-" << neighbor << ": ";
            neighbor > ANN_result.size() - 1 ?
                Output << "Not Found" << endl << "distanceLSH: " << endl:
                Output << ANN_result[neighbor].second << endl
                << "distanceLSH: " << ANN_result[neighbor].first << endl;
            Output << "distanceTrue: " << NNB_result[neighbor] << endl << endl;
        }

        Output << "tLSH: " << Lsh->ANN_time.count() << endl;
        Output << "tTrue: " << Lsh->NNB_time.count() << endl << endl;

        Output << "R-near neighbors:" << endl;
        for (auto point: SBR_result) {
            Output << point << endl;
        }
        Output << endl;
    }
    
    Output.close();

    // cout << "BRUTE SRB" << endl;
    // for (auto v: Brute_by_range(Lsh->queries_data[0])) {
    //     cout << "BRUTE SBR POINT: " << v << endl;
    // }

    Print_values();
}