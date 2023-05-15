#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>
#include <iostream>

#include "zberRegularne.h"


class SpracujVysledkyBiregularne : public SpracujVysledky{
    int reg2;
    void zapisDoSUboru() override;


public:
    SpracujVysledkyBiregularne(std::string subor, int pocet, int n2, int reg12, int reg22)
    : SpracujVysledky(subor, pocet, n2, reg12)
    , reg2(reg22)
    {
        std::cout << "zberanie vysledkov pre biregularne grafy a " << pocet << " suborov" << std::endl;

    };
};