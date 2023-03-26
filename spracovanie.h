#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>
#include <fstream>
#include <iostream>


class SpracujCele {
    int reg;
    int n;
    int reg2;

    std::ifstream suborZ;
    std::ofstream suborDo;
    int pocetSuborov;

    
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

    void grafyDoSuboru(unsigned long long pocet, const Hrany& grafy, std::ofstream& sub);
    void zapisDoSUboru();

    bool vznikneNasHrana(int u, int v, std::vector<int>& zahrnuteVrchy);
    void kombinacieHran(int ostavaDlzky, int odIndexu, const Hrany& hrany, Hrany& zatialVybrate, std::vector<int>& zahrnuteVrchy, std::set<std::vector<int>>& vysledneHrany);


public:
    SpracujCele(std::string subor, int regA, int n2, int regB)
    : reg(regA)
    , n(n2)
    , reg2(regB)
    , suborZ(subor)
    , suborDo("out-" + subor)
    {
        std::cout << reg << "-regularne grafy na " << n << " vrcholoch, navyse " << reg2 << ", zo suboru "<< subor << std::endl;

    if (!suborDo.is_open()) {
        std::cout << "Nepodarilo sa vytvorit subor a zapisat donho vysledky";
        exit(1);
    }
    
    if (!suborZ.is_open()) {
        std::cout << "nepodarilo sa otvorit a spracovat subor " << subor << std::endl;
        exit(1);
    }

    };

    void celySubor();
    
    
};