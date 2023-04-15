#include <stdio.h>
#include <iostream>
#include <chrono>

#include "generovanie.h"



int main(int argc, char *argv[])
{
   
    if (argc != 5) {
        std::cout << "zly pocet argumentov" << std::endl;
        return 1;
    }

    Generator gen(std::atoi(argv[2]), std::atoi(argv[1]), std::atoi(argv[4]), std::atoi(argv[3]));

    auto zaciatok = std::chrono::high_resolution_clock::now();
    gen.generovanie();
    auto koniec = std::chrono::high_resolution_clock::now();
    auto dlzka = std::chrono::duration_cast<std::chrono::seconds>(koniec - zaciatok).count();

    std::cout << "generovanie a spracovanie bolo ukoncene po " << dlzka << " sekundach" << std::endl;
}