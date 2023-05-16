#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "collectingRegularGraphs.h"


class SpracujVysledkyTriedy : public ColRegular{
    std::ofstream fileTo;
    void getResultsFromFile(int fileNumber) override;


public:
    SpracujVysledkyTriedy(std::string file, int number, int n2, int reg2)
    : ColRegular(file, number, n2, reg2)
    , fileTo("triedy" + std::to_string(reg) + "-" + std::to_string(n) + "-" + std::to_string(numberOfFiles) + ".txt")
    {
        std::cout << "zberanie vysledkov pre triedy a " << number << " suborov" << std::endl;
        if (!fileTo.is_open()) {
            std::cout << "Nepodarilo sa vytvorit file a zapisat donho vysledky";
            exit(1);
        }

    };
};