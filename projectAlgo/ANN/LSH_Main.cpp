#include <iostream>
#include <chrono>
#include <utility>

#include "../include/interface/LSH_interface.hpp"
//#include "../include/LSH/LSH.hpp"

int main(int argc, char const *argv[]) {

//Definition of variables that are used for error checking
 int error_LSH = 0;
 bool response = true;
 interface::ExitCode status;
 interface::Dataset queries;
 interface::Dataset dataset;
 interface::IOFiles files;
 interface::LSH::s_LSH lsh_input;
 interface::output::KNN_Output output;

//parse input of LSH
error_LSH = interface::LSH::LSH_Parse_Input(argc, argv, lsh_input, files, status);

//check for potential errors 
if(error_LSH != 0){
    interface::output::Print_Error_Message_Exit(status);
}

//parse query
}