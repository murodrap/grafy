#include <stdio.h>
#include <iostream>
#include <chrono>

#include "spracovanieBiregularne.h"
#include "spracovanieRegularne.h"

int main(int argc, char *argv[])
{
    std::string subor;
    int n;
    int k;
    int k2;
    if (argc == 4) {
        n = std::atoi(argv[1]);
        k = std::atoi(argv[2]);
        k2 = std::atoi(argv[3]);
        subor = "maxMinBireg" +  std::to_string(k) + "-" +  std::to_string(n) + "-" + std::to_string(k2) + ".txt";
    }
    else if (argc == 5) {
        std::string s(argv[1]);
        subor = s;
        n = std::atoi(argv[2]);
        k = std::atoi(argv[3]);
        k2 = std::atoi(argv[4]);
    }
    else {
        std::cout << "zly pocet argumentov" << std::endl;
        return 1;
    }

    SpracujCeleBiregularne spr(subor, k, n, k2);

    auto zaciatok = std::chrono::high_resolution_clock::now();
    spr.celySubor();
    auto koniec = std::chrono::high_resolution_clock::now();
    auto dlzka = std::chrono::duration_cast<std::chrono::seconds>(koniec - zaciatok).count();

    std::cout << "spracovanie bolo ukoncene po " << dlzka << " sekundach\n";
}