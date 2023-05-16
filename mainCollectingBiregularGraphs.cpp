#include <stdio.h>
#include <iostream>
#include "collectingBiregularGraphs.h"


int main(int argc, char *argv[])
{
    
    if (argc != 6) {
        std::cout << "zly number argumentov" << std::endl;
        return 1;
    }

    std::string file(argv[1]);

    ColBiregular spr(file, std::atoi(argv[2]), std::atoi(argv[3]), std::atoi(argv[4]), std::atoi(argv[5]));
    spr.collectResults();

    return 0;
}