#include <stdio.h>
#include <iostream>
#include "zberBiregularne.h"


int main(int argc, char *argv[])
{
    
    if (argc != 6) {
        std::cout << "zly pocet argumentov" << std::endl;
        return 1;
    }

    std::string subor(argv[1]);

    SpracujVysledkyBiregularne spr(subor, std::atoi(argv[2]), std::atoi(argv[3]), std::atoi(argv[4]), std::atoi(argv[5]));
    spr.zberVysledkov();

    return 0;
}