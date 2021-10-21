#ifndef _INTERFACE
#define _INTERFACE


#include <cstdlib>
#include <cstdint>
#include <fstream>
#include <algorithm>
#include <limits>
#include <vector>
#include <utility>

#include "interface_utilities.hpp"
#include "../items/item.hpp"


// namespace regarding interface functions
namespace interface{

  // // struct used to group the IOC (input - output - configuration) values
  // typedef struct IOCFiles{
  //   std::string input_file = "";
  //   std::string configuration_file = "";
  //   std::string output_file = "";
  // } IOCFiles;

  /* struct used to group the IO (input - output) values */
  typedef struct IOFiles{
    std::string input_file = "";
    std::string output_file = "";
    std::string query_file = "";
  } IOFiles;

  // struct used to define the dataster values
  typedef struct Dataset{
    uint32_t image_rows = 0;
    uint32_t image_columns = 0;
    uint32_t image_num = 0;
    //uint32_t magic_number = 0;
    uint8_t** images = NULL;//array of pixels
  } Dataset;


  // struct used to save dataset
  template <typename T>
  struct Data{
    uint16_t dimension = 0;
    uint32_t n = 0;
    Item<T>** items = NULL;

    Data(Dataset& dataset){
      // initialize the values 
      n = dataset.image_num;
      dimension = dataset.image_rows * dataset.image_columns;
      items = new Item<T>*[n];

      // create each item one by one
      for (int i = 0; i < n; i++){
        items[i] = new Item<T>(i, dataset.images[i], false, false);
      }
    }

    ~Data(){
      // free each item one by one
      for (int i = 0; i < n; i++){
        delete items[i];
      }
      //  delete the items array 
      delete[] items;
      items = NULL;
    }
  };


  // function used to read input from the dataset 
  int Parse_Dataset(const std::string& filename, Dataset& dataset, ExitCode& status);

  // function to free up the memory of dataset
  void Free_Dataset(Dataset& data);

  /* function used to scan the query and output files, in case they were not passed as command line parameters */
  void Scan_Input(IOFiles& files, ExitCode& status, const bool& change_dataset, const bool& change_query, const bool& change_output);


  // namespace regarding output 
  namespace output{
    // struct used to save output
    typedef struct KNN_Output{
      uint32_t n;
      std::string method;
      std::vector<int> query_id;    // item id
      std::vector<std::vector<int>> n_neighbors_id;     // knn neighbors item id 
      std::vector<std::vector<int>> r_near_neighbors_id; // item id of range search neighbors
      std::vector<std::vector<double>> approx_distance; // knn distance
      std::vector<std::vector<double>> true_distance;   // real distance
      std::vector<double> approx_time;  //time to complete kNN for 1 query
      std::vector<double> true_time;
    } KNN_Output;

    // function to write the output of LSH/HC to a file 
    int Write_Output(const std::string& outfile_name, KNN_Output& output, ExitCode& status);
  }

}
#endif
