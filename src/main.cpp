#include <stdlib.h>
#include <iostream>
#include "vfs/vfs.h"
#include "vfs/localfsentrypoint.h"

int main(int argc, char** argv)
{
    LocalFSEntryPoint cdEntry(".");

    VFS vfs;

    vfs.addEntryPoint(&cdEntry);

    std::iostream* iost = vfs.open("test.txt", std::ios::out);

    if(iost){
        (*iost)<<"test";
        vfs.close(iost);
    }

    return (EXIT_SUCCESS);
}

