#include <stdio.h>
#include <iostream>
#include <chrono>

#include "spracovanieTriedy.h"

int main(int argc, char *argv[])
{
    std::string subor;
    int n;
    int k;
    if (argc == 3) {
        n = std::atoi(argv[1]);
        k = std::atoi(argv[2]);
        subor = "triedyKostier" +  std::to_string(k) + "-" +  std::to_string(n) + ".txt";
    }
    else if (argc == 4) {
        std::string s(argv[1]);
        subor = s;
        n = std::atoi(argv[2]);
        k = std::atoi(argv[3]);
    }
    else {
        std::cout << "zly pocet argumentov" << std::endl;
        return 1;
    }

    SpracujCeleTriedy spr(subor, k, n);

    auto zaciatok = std::chrono::high_resolution_clock::now();
    spr.celySubor();
    auto koniec = std::chrono::high_resolution_clock::now();
    auto dlzka = std::chrono::duration_cast<std::chrono::seconds>(koniec - zaciatok).count();

    std::cout << "spracovanie bolo ukoncene po " << dlzka << " sekundach\n";
}