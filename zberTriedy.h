#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "zberRegularne.h"


class SpracujVysledkyTriedy : public SpracujVysledky{
    std::ofstream suborDo;
    void vyhodnotenieVysledkovSuboru(int cast) override;


public:
    SpracujVysledkyTriedy(std::string subor, int pocet, int n2, int reg2)
    : SpracujVysledky(subor, pocet, n2, reg2)
    , suborDo("triedy" + std::to_string(reg) + "-" + std::to_string(n) + "-" + std::to_string(pocetSuborov) + ".txt")
    {
        std::cout << "zberanie vysledkov pre triedy a " << pocet << " suborov" << std::endl;
        if (!suborDo.is_open()) {
            std::cout << "Nepodarilo sa vytvorit subor a zapisat donho vysledky";
            exit(1);
        }

    };
};