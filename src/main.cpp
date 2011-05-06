#include <stdlib.h>
#include <iostream>
#include "utils/utils.h"

int main(int argc, char** argv)
{
    const char* str = "12345";
    
    std::cout << utils::casts::number_cast<int>(str) << std::endl;
    
    return (EXIT_SUCCESS);
}

