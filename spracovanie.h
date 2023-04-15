#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>
#include <fstream>
#include "VypocetKostier.h"


class SpracujCele {
    int reg;
    int n;

    std::ifstream suborZ;
    std::ofstream suborDo;
    int pocetSuborov;
    VypocetKostier pocitadlo;
    int maxDrzanych = 1000;

    
    using Hrany = std::vector<std::vector<int>>;
    std::vector<Hrany> maxG;
    std::vector<Hrany> minG;
    unsigned long long maxK = 1;
    unsigned long long minK = ULLONG_MAX;
    void kontrolaHodnot(unsigned long long pocet, const Hrany& hrany);
    
    using Riadky = std::vector<std::string>;
    Hrany spracujGraf(const Riadky& riadky);
    void jedenGraf(const Riadky& graf);
    long podlaVzorca();

    void grafyDoSuboru(unsigned long long pocet, const std::vector<Hrany>& grafy, std::ofstream& sub);
    void zapisDoSUboru();


public:
    SpracujCele(std::string subor, int reg2, int n2)
    : reg(reg2)
    , n(n2)
    //, suborZ(subor)
    , suborDo(subor)
    , pocitadlo(VypocetKostier(n, reg))
    {
        std::cout << reg << "-regularne grafy na " << n << " vrcholoch zo suboru "<< subor << std::endl;
        

    if (!suborDo.is_open()) {
        std::cout << "Nepodarilo sa vytvorit subor a zapisat donho vysledky";
        exit(1);
    }
    
    //if (!suborZ.is_open()) {
    //    std::cout << "nepodarilo sa otvorit a spracovat subor " << subor << std::endl;
    //    exit(1);
    //}

    };

    void celySubor();
    
    
};