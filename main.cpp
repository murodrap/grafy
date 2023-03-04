#include <stdio.h>
#include <iostream>
#include "spracovanie.h"
#include "VypocetKostier.h"


int main(int argc, char *argv[])
{
    SpracujCele* spr;
    if (argc == 4) {
        spr = new SpracujCele(std::atoi(argv[2]), std::atoi(argv[1]), std::atoi(argv[3]));
    }
    else {
        spr = new SpracujCele(std::atoi(argv[2]), std::atoi(argv[1]), std::atoi(argv[3]), std::atoi(argv[4]));
    }
    spr->celySubor();
    
    return 0;
}