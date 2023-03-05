#include <stdio.h>
#include <iostream>
#include <chrono>
#include "spracovanie.h"
#include "VypocetKostier.h"


int main(int argc, char *argv[])
{
    if (argc != 5 && argc != 6) {
        std::cout << "zly pocet argumentov\n";
        return 1;
    }
    
    SpracujCele* spr;
    std::string subor(argv[1]);
    std::cout << "ciatme zo suboru " << subor << std::endl;

    try {
        if (argc == 5) {
            spr = new SpracujCele(subor, std::atoi(argv[3]), std::atoi(argv[2]), std::atoi(argv[4]));
        }
        else {
            spr = new SpracujCele(subor, std::atoi(argv[3]), std::atoi(argv[2]), std::atoi(argv[4]), std::atoi(argv[5]));
        }
    }
    catch (...) {
        std::cout << "zle typy argumentov\n";
        return 1;
    }

    auto zaciatok = std::chrono::high_resolution_clock::now();
    spr->celySubor();
    auto koniec = std::chrono::high_resolution_clock::now();
    auto dlzka = std::chrono::duration_cast<std::chrono::seconds>(koniec - zaciatok).count();

    std::cout << "spracovanie bolo ukoncene po " << dlzka << " sekundach\n";
    
    return 0;
}