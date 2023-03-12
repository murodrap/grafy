#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>


class SpracujCele {
    int reg;
    int n;

    std::string suborZ;
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

    void grafyDoSuboru(std::string typ, unsigned long long pocet, const std::vector<Hrany>& grafy, std::ofstream& subor);
    void grafyDoSuboru(std::string typ, unsigned long long pocet, const std::vector<std::string>& grafy, std::ofstream& subor);
    void zapisDoSUboru();
    std::pair<unsigned long long, const std::vector<std::string>> nacitanieVyslPreTyp(std::ifstream& subor);



public:
    SpracujCele(std::string subor, int reg2, int n2)
    : suborZ(subor)
    , reg(reg2)
    , n(n2)
    {
        std::cout << reg << "-regularne grafy na " << n << " vrcholoch zo suboru "<< suborZ << std::endl;
    };

    SpracujCele(std::string subor, int reg2, int n2, int pocet)
    : suborZ(subor)
    , reg(reg2)
    , n(n2)
    , pocetSuborov(pocet)
    {
        std::cout << reg << "-regularne grafy na " << n << " vrcholoch z "<< pocetSuborov << " suborov" << std::endl;
    };
    void celySubor();
    void vyhodnotenieVysledkovSubory();
    
    
};