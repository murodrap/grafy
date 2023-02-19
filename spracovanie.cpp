#pragma once
#include <stdio.h>
#include <vector>
#include <map>
#include <climits>
#include <string>
#include <sstream>
#include <cmath>
#include <iostream>
#include <fstream>
#include "VypocetKostier.h"
#include "spracovanie.h"
/*

    using Riadky = std::vector<std::string>;
    
    
    void celySubor();

*/
using Hrany = std::vector<std::vector<int>>;

void SpracujCele::kontrolaHodnot(long pocet, const Hrany& hrany) {
    //std::cout << "kostier " << pocet << "\n"; 

    if (pocet == maxK) {
        maxG.push_back(hrany);
    }

    if (pocet > maxK) {
        maxK = pocet;
        maxG.clear();
        maxG.push_back(hrany);
    }
    if (pocet == minK) {
        minG.push_back(hrany);
    }

    if (pocet < minK) {
        minK = pocet;
        minG.clear();
        minG.push_back(hrany);
    }

}

long SpracujCele::podlaVzorca() {
    std::map<int, int> hodn{{4, 16}, {6, 75}, {8, 256}, {12, 2112}};


    auto h = hodn.find(this->n);
    if (h != hodn.end()) {
        return h->second;
    }
   
    if (n%4 == 0) {
        long stvorkove = trunc(pow(8, trunc((n-3*5)/4)));
        return trunc(pow(24, 3)) * stvorkove;
    }
    long stvorkove = trunc(pow(8, trunc((n-2*5)/4)));
    return trunc(pow(24, 2)) * stvorkove;
}

Hrany SpracujCele::spracujGraf(const Riadky& riadky) {
    Hrany hrany(n*reg/2);
    int index = 0;
    for (const std::string& riadok : riadky) {
        std::stringstream ss(riadok);
        std::string vrch;
        std::string susedia;
        
        getline(ss, vrch, ':');
        vrch.pop_back();
        getline(ss, susedia, ':');
        susedia.erase(0, 1);
        //std::cout << riadok << "--" << vrch << "--\n";
        //std::cout << vrch << " ttt " << susedia;
        
        int v = stoi(vrch);
        //std::cout << v << "\n";
        std::string sused;  
        std::stringstream ss2(susedia);
        while (!ss2.eof()) {
            getline(ss2, sused, ' ');
            if (!sused.size()) {
                continue;
            }
            //std::cout << "sus " << sused << "--\n";
            int u = stoi(sused);
            if (u > v) {
                std::vector<int> hrana(2);
                hrana[0] = v - 1;
                hrana[1] = u - 1;
                hrany[index] = hrana;
                index++;
            }
        }
    }
    return hrany;
}

void SpracujCele::grafyDoSuboru(std::string typ, long pocet, const std::vector<Hrany>& grafy, std::ofstream& subor) {
    subor << typ << " " << pocet << "\n";
        
    for (const Hrany& graf : grafy) {
        subor << "[";
        bool prve = true;
        for (const std::vector<int>& hrana : graf) {
            if (prve) {
                prve = false;
            }
            else {
                subor << ", ";
            }
            subor << "(" << hrana[0] << ", " << hrana[1] << ")";
        }

        subor << "]\n";
    }

}

void SpracujCele::zapisDoSUboru() {
    std::stringstream kamUkladat;
    kamUkladat << "maxMinReg" << reg << "-" << n << ".txt";
    std::ofstream subor;
    subor.open (kamUkladat.str());
    if (subor.is_open()) {
        grafyDoSuboru("min", minK, minG, subor);
        grafyDoSuboru("max", maxK, maxG, subor);

        subor.close();
    }
    else {
        std::cout << "Unepodarilo sa vytvorit subor a zapisat donho vysledky";
    }
}
void SpracujCele::jedenGraf(const Riadky& graf) {
    Hrany hrany = spracujGraf(graf);
    long kostrier = VypocetKostier::celkovyVypocet(hrany, reg, n);
    kontrolaHodnot(kostrier, hrany);
}

void SpracujCele::celySubor() {
    
    std::ifstream subor;
    subor.open (suborZ);
    if (!subor.is_open()) {
        std::cout << "nepodarilo sa otvorit a spracovat subor";
        return;
    }
    Riadky vrcholy(n);
    long spracovanych = 0;
    int index = 0;
    std::string riadok;
    while (getline(subor, riadok) && spracovanych < pocetGrafov) {
        vrcholy.at(index) = riadok;
        index++;
        if (index == n) {
            //spracovanie grafu
            jedenGraf(vrcholy);
            index = 0;
            spracovanych++;
            if((spracovanych % 10000) == 0)
                std::cout << spracovanych << "\n";
        }
    }
    subor.close();
    zapisDoSUboru();

}