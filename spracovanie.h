#pragma once
#include <stdio.h>
#include <vector>
#include <set>
#include <climits>
#include <string>


class SpracujCele {
    int reg;
    int n;
    int reg2;
    int pocetBeziacich = 0;
    int maxBeziacich = 500;

    
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

    void grafyDoSuboru(std::string typ, unsigned long long pocet, const std::vector<Hrany>& grafy, std::ofstream& subor);
    void zapisDoSUboru();

    bool vznikneNasHrana(int u, int v, std::vector<int>& zahrnuteVrchy);
    void kombinacieHran(int ostavaDlzky, int odIndexu, const Hrany& hrany, Hrany& zatialVybrate, std::vector<int>& zahrnuteVrchy, std::set<std::vector<int>>& vysledneHrany);



public:
    SpracujCele(int reg2, int n2, int h)
    : reg(reg2)
    , n(n2)
    , reg2(h)
    {
    };
    void celySubor();
    
    
};