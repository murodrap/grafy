#include <stdio.h>
#include <iostream>
#include "rozdelovanieVysledkov.h"


int main(int argc, char *argv[])
{
    
    if (argc != 6) {
        std::cout << "zly pocet argumentov\n";
        return 1;
    }


    std::string suborZ(argv[1]);
    std::string suborDo(argv[2]);
    int pocetCasti(std::atoi(argv[3]));
    int n(std::atoi(argv[4]));
    int velkostSkupiny(std::atoi(argv[5]));

    RozdelujVysledky spr(suborZ, suborDo, pocetCasti, n, velkostSkupiny);
    spr.rozdelovanieVysledkov();

    return 0;
}