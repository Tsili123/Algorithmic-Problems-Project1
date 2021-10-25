#include "./LSH/LSH.hpp"

using namespace std;

LSH *Lsh;

int main(int argc, char *argv[]) {

    Lsh->data = store_data(argc, argv);

    Euclidean_Hash_Function(Lsh->get_L(), Lsh->get_k());

    // int counter = 0;

    // for (auto item: Lsh->data) {
    //     cout << "vector p: ";
    //     for (auto vec: item)
    //         cout << vec << ", ";  
    //     cout << endl;
    //     Calculate_Hash_Value(Lsh->get_L(), Lsh->get_k(), item);
    //     if (counter == 5)break;
    //     counter++;
    // }

    vector<vector<int>> q_vec;
    
    read_file(q_vec, Lsh->query_file);

    cout << Nearest_N_brute(q_vec.front()) << endl;
    // cout << euclidean_dis(Lsh->data[0], Lsh->data[2]) << endl;
    // cout << euclidean_dis(Lsh->data[3], Lsh->data[4]) << endl;

    Print_values();
}