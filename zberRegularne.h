#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>
#include <iostream>


class SpracujVysledky {
    int n;
    int reg;
    std::string suborZ;
    int pocetSuborov;

    int maxDrzanych = 1000;

    using Grafy = std::vector<std::string>;
    Grafy maxG;
    Grafy minG;
    unsigned long long maxK = 1;
    unsigned long long minK = ULLONG_MAX;
    void kontrolaMin(unsigned long long pocet, const Grafy& grafy);
    void kontrolaMax(unsigned long long pocet, const Grafy& grafy);
    
    void grafyDoSuboru(std::string typ, unsigned long long pocet, const Grafy& grafy, std::ofstream& subor);
    void zapisDoSUboru();
    std::pair<unsigned long long, const Grafy> nacitanieVyslPreJedenGraf(std::ifstream& subor);
    void vyhodnotenieVysledkovSuboru(int cast);



public:


    SpracujVysledky(std::string subor, int pocet, int n2, int reg2)
    : suborZ(subor)
    , pocetSuborov(pocet)
    , n(n2)
    , reg(reg2)
    {
        std::cout << "zberanie vysledkov pre " << pocet << " suborov" << std::endl;

    };
    void zberVysledkov();

    
    
    
};