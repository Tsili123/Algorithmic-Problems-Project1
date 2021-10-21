#ifndef _INTERFACE_UTILS
#define _INTERFACE_UTILS

// namespace regarding interface utilities 
namespace interface{

  //different reason for why the program could fail
  typedef enum ExitCode
  {
    FAIL,
    SUCCESS,
    NO_INPUT,
    INVALID_INPUT_LSH,
    INVALID_INPUT_HCUBE,
    INVALID_INPUT_CLUSTERING,
    INVALID_K,
    INVALID_K_DIM,
    INVALID_L,
    INVALID_M,
    INVALID_N,
    INVALID_R,
    INVALID_CLUSTERING_METHOD,
    CONFIG_INVALID_CLUSTERS,
    CONFIG_NO_CLUSTERS,
    INVALID_INFILE_PATH,
    INVALID_QFILE_PATH,
    INVALID_OUTFILE_PATH,
  } ExitCode;

  // function to check if a file exists based on path
  bool File_Exists(const std::string& path);

  // function that checks if a file can be opened 
  bool File_Accessible(const std::string& path);

  // function to read a filename that performs a loop until a valid
  void Get_Filename(std::string& filename, const std::string& type, const bool& existance);

  // namespace regarding output with the user
  namespace output{
    // function that prints image in console
    void print_Image(const uint8_t* image_vector, const uint32_t& rows, const uint32_t& columns);

    // function that shows how an LSH input should be 
    void LSH_Print_Input_Format(void);

    // function that shows how a HYPERCUBE input should be 
    void HCUBE_Print_Input_Format(void);

    // function that shows how a CLUSTERING input should be 
    void Clustering_Show_Input_Format(void);

    // function to print an error message and exit
    void Print_Error_Message_Exit(const ExitCode& code);
  }
};


#endif
