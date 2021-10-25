#include "./LSH/LSH.hpp"

using namespace std;

LSH *Lsh;

void read_f(vector<vector<int>> &vec,string input_file){
    string line;
    ifstream Data_File(input_file);
    
    if (Data_File.is_open()){
        int rows = 0;
        while(getline(Data_File,line)){
            stringstream s;
            s << line;                   //send the line to the stringstream object

            int columns = 0;    
            double d;
            vector<int> v1;

            while(s >> d){
                int num = static_cast<int>(d);
                v1.push_back(num);
                columns++;  //while there's something in the line, increase the number of columns
            } 
            vec.push_back(v1);
            //cout << columns;
            rows++;
        }
        
    }else cout << "Unable to open file"; 
    Data_File.close();
    
}

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
    
    read_f(q_vec, Lsh->query_file);

    cout << Nearest_N_brute(q_vec.front()) << endl;
    // cout << euclidean_dis(Lsh->data[0], Lsh->data[2]) << endl;
    // cout << euclidean_dis(Lsh->data[3], Lsh->data[4]) << endl;

    Print_values();
}