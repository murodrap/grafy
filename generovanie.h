#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <string>
#include <fstream>
#include "VypocetKostier.h"
#include "vseobecne.h"



class Generator {
    int reg1;
    int n1;
    int reg2;
    int n2;

    std::ofstream suborDo;
    VypocetKostier pocitadlo;

    
    using Hrany = std::vector<std::vector<int>>;
    std::vector<Hrany> maxG;
    std::vector<Hrany> minG;
    //std::set<const Hrany> najdeneGrafy;
    unsigned long long maxK = 1;
    unsigned long long minK = ULLONG_MAX;
    void kontrolaHodnot(unsigned long long pocet, const Hrany& hrany);

    void grafyDoSuboru(std::string typ, unsigned long long pocet, const std::vector<Hrany>& grafy, std::ofstream& sub);
    void zapisDoSUboru();

    void vsetkyGrafy(std::vector<int>& ostavajuceStupne, Hrany& vybrateHrany, std::vector<int>& spojeniaDo);


public:
    Generator(int reg12, int n12, int reg22, int n22)
    : reg1(reg12)
    , n1(n12)
    , reg2(reg22)
    , n2(n22)
    , pocitadlo(VypocetKostier(n1 + n2, 0))
    {
        std::cout << reg1 << " a " << reg2 << "-regularne grafy na " << n1 << " a " << n2 << " vrcholoch" << std::endl;
        if (!VseobecneFunkcie::existujeGraf(n1, reg1, n2, reg2)) {
            exit(1);
        }
    }


    void generovanie();
    
    
};