#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>
#include <mutex>


class SpracujVysledky {
    int n;
    int reg;
    int reg2;
    std::string suborZ;
    int pocetSuborov;
    std::mutex mtxHodnoty;

    int maxDrzanych = 1000;

    
    using Grafy = std::vector<std::string>;
    Grafy maxG;
    Grafy minG;
    unsigned long long maxK = 1;
    unsigned long long minK = ULLONG_MAX;
    void kontrolaMin(unsigned long long pocet, const std::string& grafy);
    void kontrolaMax(unsigned long long pocet, const std::string& grafy);
    
    void grafyDoSuboru(std::string typ, unsigned long long pocet, const Grafy& grafy, std::ofstream& subor);
    void zapisDoSUboru();
    std::pair<unsigned long long, const std::string> nacitanieVyslPreJedenGraf(std::ifstream& subor);
    void vyhodnotenieVysledkovSuboru(int cast);



public:


    SpracujVysledky(std::string subor, int pocet, int n2, int regA, int regB)
    : suborZ(subor)
    , pocetSuborov(pocet)
    , n(n2)
    , reg(regA)
    , reg2(regB)
    , mtxHodnoty()
    {
        std::cout << "zberanie vysledkov pre " << pocet << " suborov\n";

    };
    void zberVysledkov();

    
    
    
};