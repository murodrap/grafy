#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>
#include <iostream>

#include "collectingRegularGraphs.h"


class ColBiregular : public ColRegular{
    int reg2;
    void writeToFile() override;


public:
    ColBiregular(std::string file, int number, int n2, int reg12, int reg22)
    : ColRegular(file, number, n2, reg12)
    , reg2(reg22)
    {
        std::cout << "zberanie vysledkov pre biregularne graphs a " << number << " suborov" << std::endl;

    };
};