#pragma once
#include <stdio.h>
#include <vector>
#include <set>
#include <climits>
#include <string>

#include "spracovanieRegularne.h"
#include "vseobecne.h"


class SpracujCeleBiregularne : public SpracujCele{
    int reg2;
    
    using Hrany = std::vector<std::vector<int>>;
    using Riadky = std::vector<std::string>;

    bool vznikneNasHrana(int u, int v, std::vector<int>& zahrnuteVrchy);
    void kombinacieHran(int ostavaDlzky, int odIndexu, const Hrany& hrany, Hrany& zatialVybrate, std::vector<int>& zahrnuteVrchy, std::set<std::vector<int>>& vysledneHrany);
    void jedenGraf(const Riadky& graf) override;


public:
    SpracujCeleBiregularne(std::string subor, int reg12, int n2, int reg22)
    : SpracujCele(subor, 0, n2+1)
    , reg2(reg22)
    {
        reg = reg12;
        n -= 1;
        std::cout << reg << "-regularne na " << n << " vrcholoch, navyse " << reg2 << "-regularny" << std::endl;
        if (!VseobecneFunkcie::existujeGraf(n, reg, 1, reg2)) {
            pocitadlo.koniec();
            exit(1);
        }
    };
    
};