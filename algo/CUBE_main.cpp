#include "./Handling_input/Handling_input_cube.hpp"
#include "./LSH/hypercube.hpp"
#include <cctype>
class Hypercube;
using namespace std;
Hypercube *Hpb;

// ./cube -i ./files/input_small_id -q ./files/query_small_id -o output_file

int main(int argc, char *argv[]) {

    store_data(argc, argv);

    read_file(Hpb->query_data, Hpb->query_file);

    list<int> neighbors;
    list<double> neighbors_dists;
    Hpb->RNeighbors(Hpb->query_data[0],Hpb->R,neighbors, neighbors_dists);
    neighbors_dists.sort();
    for(auto i:neighbors_dists)
        std::cout << i << "\n";

    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    vector<pair<long double, int>> near_items;
    Hpb->nNeighbor(Hpb->query_data[0],5, near_items);

     for(auto i:near_items)
         std::cout << i.second << " " << i.first  << "\n";
    // for (auto v: Nearest_N_search(Lsh->queries_data[10])) {
    //     cout << v.first << ", " << v.second << endl;
    // }
    // int point = Nearest_N_brute(Lsh->queries_data[10]);
    // cout << "BRUTE NEAREST POINT: " << point << endl;

    // cout << "SEARCH BY RANGE" << endl;
    // for (auto v: Search_by_range(Lsh->queries_data[10])) {
    //     cout << v.first << ", " << v.second << endl;
    // }

    // cout << "BRUTE SRB" << endl;
    // for (auto v: Brute_by_range(Lsh->queries_data[10])) {
    //     cout << "BRUTE SBR POINT: " << v << endl;
    // }
    
    // cout << euclidean_dis(Lsh->data[0], Lsh->data[2]) << endl;
    // cout << euclidean_dis(Lsh->data[3], Lsh->data[4]) << endl;

    // Print_values();
}