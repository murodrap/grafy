#include <stdio.h>
#include <iostream>
#include "collectingRegularGraphs.h"


int main(int argc, char *argv[])
{
    
    if (argc != 5) {
        std::cout << "Incorrect number of arguments" << std::endl;
        return 1;
    }

    std::string file(argv[1]);

    ColRegular col(file, std::atoi(argv[2]), std::atoi(argv[3]), std::atoi(argv[4]));
    col.collectResults();

    return 0;
}
