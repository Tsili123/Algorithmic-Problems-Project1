#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include "../headers/read_file.hpp"

using namespace std;

bool string_operation(char ** str,char *str2,string& str3,int i);
bool number_operation(char ** str,char *str2,int num,int i);

//g++ -c -o main.o main.cpp
//g++ -o lsh main.o
//  ./lsh -i doc
//  /home/users/sdi1700170/projectAlgorithms/files/input_small_id
// ./lsh -i input_small_id -q query_file -k 4 -L 5 -o output -N 1 -R 1000
// ./lsh -i input_small_id -q query_file -k 4 -L 5 -o output -N 1 -R 1000
void read_file(vector<vector<int>> &vec,string input_file){
    string line;
    ifstream myfile(input_file);
    
    if (myfile.is_open()){
        int rows = 0;
        while(getline(myfile,line)){
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
        cout << rows << endl;
        
    }else cout << "Unable to open file"; 
    myfile.close();

}

bool string_operation(char ** str,char *str2,string &str3,int i){
    if(strcmp(str[i],str2)==0){
            str3 = string(str[i+1]);
            cout << str3 << endl;
            return true;
    }
    else{//error case
        cout << "Error in command line arguments:" << endl;
        cout << "Expected " << string(str2) << " but you typed " << string(str[i]) << endl;
        return false;
    }
}

bool number_operation(char ** str,char *str2,int num,int i){
    if(strcmp(str[i],str2)==0){
            num = atoi(str[i+1]);
            cout << num << endl;
            return true;
    }
    else{
        //error case
        cout << "Error in command line arguments:" << endl;
        cout << "Expected " << string(str2) << " but you typed " << string(str[i]) << endl;
        return false;
    }
}

int main(int argc,char** argv){
    string input_file,query_file,output_file;
    int K,L,M,N,R;

    if(argc!=7 && argc != 15){
        cout << "Error in command line arguments:" << endl;
        cout << "argc " << argc << endl;
        cout << "Program exiting due to error ..." << endl;
        return 1;
    }

    if(strcmp(argv[0],"./lsh")==0){
        cout << "We are in main" << endl;

        int i=1;
        
        if(argc == 7){//no param arguments
            if(string_operation(argv,"-i",input_file,i) == false){
                cout << "Program exiting due to error ..." << endl;
                return 1;
            }

            i=i+2;
            if(string_operation(argv,"-q",query_file,i) == false){
                cout << "Program exiting due to error ..." << endl;
                return 1;
            }

            i=i+2;
            if(string_operation(argv,"-o",output_file,i) == false){
                cout << "Program exiting due to error ..." << endl;
                return 1;
            }
            K=4;
            L=5;
            N=1;
            R=10000;
        }else if(argc == 15){ //param arguments
            
            if(string_operation(argv,"-i",input_file,i) == false){
                cout << "Program exiting due to error ..." << endl;
                return 1;
            }

            i=i+2;

            if(string_operation(argv,"-q",query_file,i) == false){
                cout << "Program exiting due to error ..." << endl;
                return 1;
            }

            i=i+2;
            if(number_operation(argv,"-k",K,i) == false){
                cout << "Program exiting due to error ..." << endl;
                return 1;
            }
            
            i=i+2;
            if(number_operation(argv,"-L",L,i) == false){
                cout << "Program exiting due to error ..." << endl;
                return 1;
            }

            i=i+2;
            if(string_operation(argv,"-o",output_file,i) == false){
                cout << "Program exiting due to error ..." << endl;
                return 1;
            }

            i=i+2;
            if(number_operation(argv,"-N",N,i) == false){
                cout << "Program exiting due to error ..." << endl;
                return 1;
            }
            
            i=i+2;
            if(number_operation(argv,"-R",R,i) == false){
                cout << "Program exiting due to error ..." << endl;
                return 1;
            }

        } 
    }
    vector<vector<int>> vec;
    cout << input_file << endl;
    read_file(vec,input_file);
    cout << vec.size() << endl;
    
    //debug
    for (int j = 0; j < vec[1].size(); j++)
    {
            cout << vec[1][j] << " ";
    }

    cout << endl;
}