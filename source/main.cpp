#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

bool string_operation(char ** str,char *str2,string str3,int i);
bool number_operation(char ** str,char *str2,int num,int i);

//g++ -c -o main.o main.cpp
    //g++ -o lsh main.o
    //./lsh -i doc

bool string_operation(char ** str,char *str2,string str3,int i){
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
            N=1
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
}