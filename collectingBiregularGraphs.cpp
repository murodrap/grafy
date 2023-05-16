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

#include "collectingBiregularGraphs.h"
#include "collectingRegularGraphs.h"

void ColBiregular::writeToFile() {

    std::stringstream kamUkladat;
    kamUkladat << "maxMinBireg" << reg << "-" << n << "-" << reg2 << "-" << numberOfFiles << ".txt";
    std::ofstream subor2;
    subor2.open (kamUkladat.str());
    if (subor2.is_open()) {
        graphsToFile("min", minK, minG, subor2);
        graphsToFile("max", maxK, maxG, subor2);
        subor2.close();
    }
    else {
        std::cout << "Nepodarilo sa vytvorit file a zapisat donho vysledky";
    }
    
}