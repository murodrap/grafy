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


void SpracujVysledkyTriedy::getResultsFromFile(int fileNumber) {
    std::ifstream file;
    std::stringstream meno;
    meno << fileFrom << "-" << fileNumber;
    file.open(meno.str());
    if (!file.is_open()) {
        std::cout << "nepodarilo sa otvorit file " << meno.str() << std::endl;
        return;
    }
    std::string riadok;
    std::getline(file, riadok);

    std::istringstream iss(riadok);
    unsigned long long pocetGrafov;
    iss >> pocetGrafov;
    std::getline(file, riadok);
    for (unsigned long long i = 0; i < pocetGrafov; i++) {
        std::getline(file, riadok);
        fileTo << riadok << std::endl;
    }
   
    file.close();
    fileTo.close();
}
