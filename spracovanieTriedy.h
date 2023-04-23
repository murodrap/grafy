#pragma once
#include <stdio.h>
#include <vector>
#include <set>
#include <climits>
#include <string>

#include "spracovanieRegularne.h"
#include "vsetkyKostry.h"


class SpracujCeleTriedy : public SpracujCele{
    int reg2;
    Onete o;
    std::vector<std::pair<unsigned long long, unsigned long long>> kostryTriedyPocty;
    
    using Hrany = std::vector<std::vector<int>>;
    using Riadky = std::vector<std::string>;

    void jedenGraf(const Riadky& graf) override;
    void zapisDoSUboru() override;


public:
    SpracujCeleTriedy(std::string subor, int reg2, int n2)
    : SpracujCele(subor, reg2, n2)
    , o(n2, n2 * reg2 / 2)
    {
        
    };
    
};