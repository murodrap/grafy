#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>
#include <tuple>
#include <iostream>
#include <fstream>
#include "oneapi/tbb/parallel_pipeline.h"


class SpracujCele {
    int reg;
    int n;
    int pocetBeziacich = 0;
    int maxBeziacich = 500;
    long spracovanych = 0;

    bool zacatyGraf = false;
    int pocetGrafov;
    int nacitanychGrafov = 0;
    bool koniec = false;
    int maxSucasneSpracovanych;

    mutable std::ifstream subor;


    
    using Hrany = std::vector<std::vector<int>>;
    using Riadky = std::vector<std::string>;
    using SkupinaGrafov = std::vector<Riadky>;
    std::vector<Hrany> maxG;
    std::vector<Hrany> minG;
    unsigned long long maxK = 1;
    unsigned long long minK = ULLONG_MAX;
    void kontrolaHodnot(unsigned long long pocet, const Hrany& hrany);
    std::string suborZ;
    
    
    Hrany* spracujGraf(const Riadky& riadky);
    //std::pair<std::pair<long, Hrany*>, std::pair<long, Hrany*>> skupinaGrafov(std::vector<Riadky* riadky>* grafy);
    std::pair<unsigned long long, Hrany*> jedenGraf(const Riadky& graf);
    long podlaVzorca();

    void grafyDoSuboru(std::string typ, unsigned long long pocet, const std::vector<Hrany>& grafy, std::ofstream& subor);
    void grafyDoSuboru(std::string typ, unsigned long long pocet, const std::vector<std::string>& grafy, std::ofstream& subor);
    void zapisDoSUboru();

    std::pair<SkupinaGrafov*, int> citanie(oneapi::tbb::flow_control& fc);
    std::vector<std::pair<unsigned long long, Hrany*>>* spracovanieSkupiny(std::pair<SkupinaGrafov*, int> grafyPocet);
    void vyhodnocovanie(std::vector<std::pair<unsigned long long, Hrany*>>* poctyGrafy);
    std::pair<unsigned long long, const std::vector<std::string>> nacitanieVyslPreTyp(std::ifstream& subor);
    



public:
    SpracujCele(std::string subor, int reg2, int n2, int maxSucasneSPracovanych2, int pocetGrafov2 = 10000)
    : suborZ(subor)
    , reg(reg2)
    , n(n2)
    , maxSucasneSpracovanych(maxSucasneSPracovanych2)
    , pocetGrafov(pocetGrafov2)
    {
            std::cout << reg << "-regularne grafy na " << n << " vrcholoch, sucasne " << maxSucasneSpracovanych << ", po kusoch " << pocetGrafov << std::endl;
    };
    void celySubor();
    void vyhodnotenieVysledkovSubory();
    
    
};