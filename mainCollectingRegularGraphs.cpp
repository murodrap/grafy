#include <stdio.h>
#include <iostream>
#include "collectingRegularGraphs.h"


int main(int argc, char *argv[])
{
    
    if (argc != 5) {
        std::cout << "zly number argumentov" << std::endl;
        return 1;
    }

    std::string file(argv[1]);

    ColRegular spr(file, std::atoi(argv[2]), std::atoi(argv[3]), std::atoi(argv[4]));
    spr.collectResults();

    return 0;
}
