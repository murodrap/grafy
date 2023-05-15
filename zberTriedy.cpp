#include <stdio.h>
#include <vector>
#include <map>
#include <climits>
#include <string>
#include <sstream>
#include <cmath>
#include <iostream>
#include <fstream>

#include "zberTriedy.h"


void SpracujVysledkyTriedy::vyhodnotenieVysledkovSuboru(int cast) {
    std::ifstream subor;
    std::stringstream meno;
    meno << suborZ << "-" << cast;
    subor.open(meno.str());
    if (!subor.is_open()) {
        std::cout << "nepodarilo sa otvorit subor " << meno.str() << std::endl;
        return;
    }
    std::string riadok;
    std::getline(subor, riadok);

    std::istringstream iss(riadok);
    unsigned long long pocetGrafov;
    iss >> pocetGrafov;
    std::getline(subor, riadok);
    for (unsigned long long i = 0; i < pocetGrafov; i++) {
        std::getline(subor, riadok);
        suborDo << riadok << std::endl;
    }
   
    subor.close();
    suborDo.close();
}
