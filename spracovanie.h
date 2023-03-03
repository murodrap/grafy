#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>
#include <tuple>


class SpracujCele {
    int reg;
    int n;
    int pocetBeziacich = 0;
    int maxBeziacich = 500;
    long spracovanych = 0;

    bool zacatyGraf = false;
    int pocetGrafov = 10000;
    int nacitanychGrafov = 0;
    bool koniec = false;

    
    using Hrany = std::vector<std::vector<int>>;
    std::vector<Hrany> maxG;
    std::vector<Hrany> minG;
    long maxK = 1;
    long minK = LONG_MAX;
    void kontrolaHodnot(long pocet, const Hrany& hrany);
    using Riadky = std::vector<std::string>;
    
    Hrany* spracujGraf(const Riadky& riadky);
    //std::pair<std::pair<long, Hrany*>, std::pair<long, Hrany*>> skupinaGrafov(std::vector<Riadky* riadky>* grafy);
    std::pair<long, Hrany*> jedenGraf(const Riadky& graf);
    long podlaVzorca();

    void grafyDoSuboru(std::string typ, long pocet, const std::vector<Hrany>& grafy, std::ofstream& subor);
    void zapisDoSUboru();



public:
    SpracujCele(int reg2, int n2)
    : reg(reg2)
    , n(n2)
    {
    };
    void celySubor();
    
    
};