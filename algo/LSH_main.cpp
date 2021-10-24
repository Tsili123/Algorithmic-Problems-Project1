#include "./LSH/LSH.hpp"

using namespace std;

int k; /* #LSH Functions */

int L; /* #Hash Tables  */

int main(int argc, char *argv[]) {

    vector<vector<int>> data = store_data(argc, argv);

    Initialize_Hash_parameters();
    
    Euclidean_Hash_Function(L, k);

    int counter = 0;

    for (auto item: data) {
        cout << "vector t: ";
        for (auto vec: item)
            cout << vec << ", ";  
        cout << endl;
        Calculate_Hash_Value(L, k, item);
        if (counter == 5)break;
        counter++;
    }

    // cout << euclidean_dis(data[0], data[1]) << endl;
    // cout << euclidean_dis(data[0], data[2]) << endl;
    // cout << euclidean_dis(data[3], data[4]) << endl;

    Print_values(L, k);
}