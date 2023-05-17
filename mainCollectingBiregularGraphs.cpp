#include <stdio.h>
#include <iostream>
#include "collectingBiregularGraphs.h"


int main(int argc, char *argv[])
{
    
    if (argc != 6) {
        std::cout << "Incorrect number of arguments" << std::endl;
        return 1;
    }

    std::string file(argv[1]);

    ColBiregular col(file, std::atoi(argv[2]), std::atoi(argv[3]), std::atoi(argv[4]), std::atoi(argv[5]));
    col.collectResults();

    return 0;
}