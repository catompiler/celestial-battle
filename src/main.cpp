#include <stdlib.h>
#include <sstream>
#include <iostream>
#include "config/config.h"

const char* config_data =
" // test config\n\
 /* some comment */ \n\
 group1 //{ \n\
/* { */ { \n\
    param1 = -0.10e+2 ; \n\
    group2 { \n\
        param2 = \"/*\\\"*/\" ; \n\
    }\n\
}\n\
param0 = value0 ;\n";

int main(int argc, char** argv)
{
    std::string config_str(config_data);
    std::istringstream istrst(config_str);
    
    Config config;
    
    config.read(istrst);
    
    return (EXIT_SUCCESS);
}

