#include "./LSH/bucket.hpp"

using namespace std;

LSH *Lsh;

int main(int argc, char *argv[]) {

    Lsh->data = store_data(argc, argv);

    read_file(Lsh->queries_data, Lsh->query_file);

    LSH_Insert_Points_To_Buckets(Lsh);

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

    // Print_values();

    for (auto v: Nearest_N_search(Lsh->queries_data[10])) {
        cout << v.first << ", " << v.second << endl;
    }
    int point = Nearest_N_brute(Lsh->queries_data[10]);
    cout << "BRUTE NEAREST POINT: " << point << endl;
    // cout << euclidean_dis(Lsh->data[0], Lsh->data[2]) << endl;
    // cout << euclidean_dis(Lsh->data[3], Lsh->data[4]) << endl;
}