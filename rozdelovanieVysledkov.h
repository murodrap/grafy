#pragma once
#include <stdio.h>
#include <vector>
#include <fstream>
#include <climits>
#include <string>
#include <mutex>


class RozdelujVysledky {
    
    std::string suborZ;
    std::string suborDo;
    int pocetSuborov;
    int n;
    int velkostSkupiny;

    std::mutex mtxPosielanie;
    std::vector<std::mutex> mtxSubory;
    int komuPoslat = 0;

    std::vector<std::ofstream> suboryVon;

    
    using Graf = std::vector<std::string>;
    using Grafy = std::vector<Graf>;

    
    void grafyDoSuboru(const Grafy& grafy);
    void zbieranieGrafovSuboru(int cast);



public:


    RozdelujVysledky(std::string subor1, std::string subor2, int pocet, int n2, int velkostSkupiny2)
    : suborZ(subor1)
    , suborDo(subor2)
    , pocetSuborov(pocet)
    , n(n2)
    , velkostSkupiny(velkostSkupiny2)
    , mtxPosielanie()
    , mtxSubory(pocetSuborov)
    {
        std::cout << "rozdelovanie vysledkov pre " << pocet << " suborov na " << n << " vrcholov, skupina " << velkostSkupiny << std::endl;    
    };
    void rozdelovanieVysledkov();
};
