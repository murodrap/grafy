#include <stdio.h>
#include <vector>
#include <map>
#include <climits>
#include <string>
#include <sstream>
#include <cmath>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex> 

#include "zberBiregularne.h"
#include "zberRegularne.h"

void SpracujVysledkyBiregularne::zapisDoSUboru() {

    std::stringstream kamUkladat;
    kamUkladat << "maxMinBireg" << reg << "-" << n << "-" << reg2 << "-" << pocetSuborov << ".txt";
    std::ofstream subor2;
    subor2.open (kamUkladat.str());
    if (subor2.is_open()) {
        grafyDoSuboru("min", minK, minG, subor2);
        grafyDoSuboru("max", maxK, maxG, subor2);
        subor2.close();
    }
    else {
        std::cout << "Nepodarilo sa vytvorit subor a zapisat donho vysledky";
    }
    
}