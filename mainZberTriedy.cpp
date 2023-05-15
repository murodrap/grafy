#include <stdio.h>
#include <iostream>
#include "zberTriedy.h"


int main(int argc, char *argv[])
{
    
    if (argc != 5) {
        std::cout << "zly pocet argumentov" << std::endl;
        return 1;
    }

    std::string subor(argv[1]);

    SpracujVysledkyTriedy spr(subor, std::atoi(argv[2]), std::atoi(argv[3]), std::atoi(argv[4]));
    spr.zberVysledkov();

    return 0;
}