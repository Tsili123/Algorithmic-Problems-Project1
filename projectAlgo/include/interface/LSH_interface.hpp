#ifndef _LSH_INTERFACE
#define _LSH_INTERFACE

#include <cstdint>
#include <cstdlib>
#include "interface.hpp"

// Namespace for interface
namespace interface{
    // Namespace for LSH
    namespace LSH{
      // struct used to define the LSH input
      typedef struct s_LSH{
        uint8_t k = 4;
        uint8_t L = 5;
        uint32_t N = 1;
        double R = 10000.0;
      } s_LSH;

      // function to parse command line args
      int LSH_Parse_Input(const int& argc, const char* argv[], s_LSH& input, IOFiles& file, ExitCode& status);
    }
}

#endif
