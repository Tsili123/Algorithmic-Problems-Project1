#include "./LSH/LSH.hpp"

using namespace std;

LSH *Lsh;

int main(int argc, char *argv[]) {

    vector<vector<int>> data = store_data(argc, argv);
    
    Euclidean_Hash_Function(Lsh->get_L(), Lsh->get_k());

    int counter = 0;

    for (auto item: data) {
        cout << "vector p: ";
        for (auto vec: item)
            cout << vec << ", ";  
        cout << endl;
        Calculate_Hash_Value(Lsh->get_L(), Lsh->get_k(), item);
        if (counter == 5)break;
        counter++;
    }

    cout << euclidean_dis(data[0], data[1]) << endl;
    cout << euclidean_dis(data[0], data[2]) << endl;
    cout << euclidean_dis(data[3], data[4]) << endl;

    Print_values();
}