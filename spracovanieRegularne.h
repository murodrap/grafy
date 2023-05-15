#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>
#include <fstream>
#include <iostream>
#include "vypocetKostier.h"


class SpracujCele {
    

    
    
    int maxDrzanych = 1000;

    
    using Hrany = std::vector<std::vector<int>>;
    std::vector<Hrany> maxG;
    std::vector<Hrany> minG;
    long long maxK = 1;
    long long minK = ULLONG_MAX;
    
    
    using Riadky = std::vector<std::string>;
    
    virtual void jedenGraf(const Riadky& graf);
    long podlaVzorca();

    void grafyDoSuboru(long long pocet, const std::vector<Hrany>& grafy, std::ofstream& sub);
    virtual void zapisDoSUboru();

protected:
    int reg;
    int n;
    std::ofstream suborDo;
    VypocetKostier pocitadlo;
    void kontrolaHodnot(long long pocet, const Hrany& hrany);
    Hrany spracujGraf(const Riadky& riadky);


public:
    SpracujCele(std::string subor, int reg2, int n2)
    : reg(reg2)
    , n(n2)
    , suborDo(subor)
    , pocitadlo(VypocetKostier(n, reg))
    {
        std::cout << reg << "-regularne grafy na " << n << " vrcholoch do suboru "<< subor << std::endl;

        if (!suborDo.is_open()) {
            std::cout << "Nepodarilo sa vytvorit subor a zapisat donho vysledky" << std::endl;
            exit(1);
        }
    };

    void celySubor();
    
    
};
