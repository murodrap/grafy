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

#include "zberRegularne.h"

using Grafy = std::vector<std::string>;


void SpracujVysledky::kontrolaMin(long long pocet, const Grafy& grafy) {
    if (pocet == minK) {
        minG.insert(minG.end(), grafy.begin(), grafy.end());
    }

    if (pocet < minK) {
        minK = pocet;
        minG.clear();
        minG.insert(minG.end(), grafy.begin(), grafy.end());
    }
}

void SpracujVysledky::kontrolaMax(long long pocet, const Grafy& grafy) {
    if (pocet == maxK) {
        if (maxG.size() < maxDrzanych) {
            maxG.insert(maxG.end(), grafy.begin(), grafy.end());
        }
    }

    if (pocet > maxK) {
        maxK = pocet;
        maxG.clear();
        maxG.insert(maxG.end(), grafy.begin(), grafy.end());
    }

}


void SpracujVysledky::grafyDoSuboru(std::string typ, unsigned long long pocet, const Grafy& grafy, std::ofstream& subor) {
    subor << typ << " " << grafy.size() << " " << pocet << "\n";
        
    for (const std::string& graf: grafy) {
        subor << graf << std::endl;
    }

}

void SpracujVysledky::zapisDoSUboru() {

    std::stringstream kamUkladat;
    kamUkladat << "maxMinReg" << reg << "-" << n << "-" << pocetSuborov << ".txt";
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

std::pair<long long, const Grafy> SpracujVysledky::nacitanieVyslPreJedenGraf(std::ifstream& subor) {
    std::string riadok;
    std::string kus;
    std::getline(subor, riadok);
    std::istringstream iss(riadok);
    long long kostier;
    int pocetGrafov;
    iss >> kus;
    if (kus == "0") {
        return std::make_pair(0, Grafy());
    }
    iss >> pocetGrafov;
    iss >> kostier;
    Grafy grafy = Grafy();
    grafy.reserve(pocetGrafov);
    
    for (int i = 0; i < pocetGrafov; i++) {
        std::string graf;
        std::getline(subor, graf);
        grafy.emplace_back(graf);
    }
    
    return std::make_pair(kostier, std::move(grafy));
}


void SpracujVysledky::vyhodnotenieVysledkovSuboru(int cast) {
    std::ifstream subor;

    std::stringstream meno;
    meno << suborZ << "-" << cast;
    subor.open(meno.str());
    if (!subor.is_open()) {
        std::cout << "nepodarilo sa otvorit subor " << meno.str() << std::endl;
        return;
    }

    std::pair<long long, const Grafy> vyslG = nacitanieVyslPreJedenGraf(subor);
    long long kostier = vyslG.first;
    if (kostier == 0) {
        subor.close();
        return;
    }
    const Grafy& grafy = vyslG.second;

    kontrolaMin(kostier, grafy);

    std::pair<long long, const Grafy> vyslG2 = nacitanieVyslPreJedenGraf(subor);
    long long kostier2 = vyslG2.first;
    const Grafy& grafy2 = vyslG2.second;

    kontrolaMax(kostier2, grafy2);
   
    subor.close();
}

void SpracujVysledky::zberVysledkov() {
    for (int i = 1; i <= pocetSuborov; i++) {
        vyhodnotenieVysledkovSuboru(i);
    }    
    zapisDoSUboru();
}