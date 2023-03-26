#include <stdio.h>
#include <iostream>
#include "zbieranieVysledkov.h"


int main(int argc, char *argv[])
{
    
    if (argc != 6) {
        std::cout << "zly pocet argumentov\n";
        return 1;
    }


    std::string subor(argv[1]);

    SpracujVysledky spr(subor, std::atoi(argv[2]), std::atoi(argv[3]), std::atoi(argv[4]), std::atoi(argv[5]));
    spr.zberVysledkov();

    return 0;
}