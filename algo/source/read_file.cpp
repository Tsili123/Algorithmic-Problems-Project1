#include "../headers/read_file.hpp"

// void read_file(vector<vector<int>>& vec,string input_file){
//     string line;
//     ifstream myfile (input_file);
  
//     if (myfile.is_open()){
//         int rows = 0;
//         while(getline(myfile,line)){
//             stringstream s;
//             s << line;                   //send the line to the stringstream object

//             int columns = 0;    
//             double value;
//             vector<int> v1;

//             while(s >> value){
//                 int num = atoi(s);
//                 v1.push_back(num);
//                 columns++;  //while there's something in the line, increase the number of columns
//             } 
//             vec.push_back(v1);
//             //cout << columns;
//             rows++;
//         }
//         cout << rows << endl;
//         cout < columns << endl;
//         myfile.close();
//     }else cout << "Unable to open file"; 

// }