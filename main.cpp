#include <stdio.h>
#include <iostream>
#include <chrono>
#include "spracovanie.h"
#include "VypocetKostier.h"


int main(int argc, char *argv[])
{
    
    if (argc != 4) {
        std::cout << "zly pocet argumentov\n";
        return 1;
    }

    std::string subor(argv[1]);
    SpracujCele spr(subor, std::atoi(argv[3]), std::atoi(argv[2]));

    auto zaciatok = std::chrono::high_resolution_clock::now();
    spr.celySubor();
    auto koniec = std::chrono::high_resolution_clock::now();
    auto dlzka = std::chrono::duration_cast<std::chrono::seconds>(koniec - zaciatok).count();

    std::cout << "spracovanie bolo ukoncene po " << dlzka << " sekundach\n";
}