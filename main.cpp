#include <stdio.h>
#include <iostream>
#include "spracovanie.h"
#include "VypocetKostier.h"


int main(int argc, char *argv[])
{
    if (argc != 4 && argc != 5) {
        std::cout << "zly pocet argumentov\n";
        return 1;
    }
    
    SpracujCele* spr;
    try {
        if (argc == 4 || std::atoi(argv[4]) <= 0) {
            spr = new SpracujCele(std::atoi(argv[2]), std::atoi(argv[1]), std::atoi(argv[3]));
        }
        else {
            spr = new SpracujCele(std::atoi(argv[2]), std::atoi(argv[1]), std::atoi(argv[3]), std::atoi(argv[4]));
        }
    }
    catch (...) {
        std::cout << "zle typy argumentov\n";
        return 1;
    }
    spr->celySubor();
    
    return 0;
}