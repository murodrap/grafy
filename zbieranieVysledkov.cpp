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

#include "zbieranieVysledkov.h"


// export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/terezia/oneTbbInstallation/lib

using Grafy = std::vector<std::string>;


void SpracujVysledky::kontrolaMin(unsigned long long pocet, const std::string& graf) {
    if (pocet == minK) {
        if (minG.size() < maxDrzanych) {
            minG.push_back(graf);
        }
        
    }

    if (pocet < minK) {
        minK = pocet;
        minG.clear();
        minG.push_back(graf);
    }
}

void SpracujVysledky::kontrolaMax(unsigned long long pocet, const std::string& graf) {
    if (pocet == maxK) {
        if (maxG.size() < maxDrzanych) {
            maxG.push_back(graf);
        }
        
    }

    if (pocet > maxK) {
        maxK = pocet;
        maxG.clear();
        maxG.push_back(graf);
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
    //std::cout << kamUkladat.str() << std::endl;
    if (subor2.is_open()) {
        grafyDoSuboru("min", minK, minG, subor2);
        grafyDoSuboru("max", maxK, maxG, subor2);
        subor2.close();
    }
    else {
        std::cout << "Unepodarilo sa vytvorit subor a zapisat donho vysledky";
    }
    
}

std::pair<unsigned long long, const std::string> SpracujVysledky::nacitanieVyslPreJedenGraf(std::ifstream& subor) {
    //std::cout << "nacitany\n";
    std::string riadok;
    std::getline(subor, riadok);
    std::istringstream iss(riadok);
    unsigned long long kostier;
    iss >> kostier;
    if (!kostier) {
        return std::make_pair(0, "");
    }
    std::string graf;
    //std::cout << "pocet nacitany\n";
    std::getline(subor, riadok);
    //std::cout << kostier << "-" << riadok << "-\n";
    graf = std::move(riadok);
    //std::cout << "graf nacitany\n";
    return std::make_pair(kostier, std::move(graf));
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
    //std::cout << cast << "aaaaaaaaaaa\n";
    while (subor.good()) {
        std::pair<unsigned long long, const std::string> vyslG = nacitanieVyslPreJedenGraf(subor);
        unsigned long long kostier = vyslG.first;
        const std::string& graf = vyslG.second;
        if (!kostier) {
            break;
        }
        //std::cout << kostier << std::endl;
        //std::cout << cast << "bbbbbbbbbbbbbbb\n";
        mtxHodnoty.lock();
        kontrolaMin(kostier, graf);
        kontrolaMax(kostier, graf);
        mtxHodnoty.unlock();
        //std::cout << cast << "cccccccccc\n";
    }
    subor.close();
}

void SpracujVysledky::zberVysledkov() {
    std::vector<std::thread> citace;
    //vyhodnotenieVysledkovSuboru(1);
    
    for (int i = 1; i <= pocetSuborov; i++) {
        //std::thread* t = new std::thread(&SpracujVysledky::vyhodnotenieVysledkovSuboru, this, i);
        //citace.push_back(t);
        citace.emplace_back(std::thread(&SpracujVysledky::vyhodnotenieVysledkovSuboru, this, i));
    }
    //std::cout << citace.size() << std::endl;
    for (int i = 0; i < pocetSuborov; i++) {
        if (citace[i].joinable()) {
            citace[i].join();
        }
    }
    
    zapisDoSUboru();
}



