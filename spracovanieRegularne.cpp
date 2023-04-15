#include <stdio.h>
#include <vector>
#include <map>
#include <climits>
#include <string>
#include <sstream>
#include <cmath>
#include <iostream>
#include <fstream>
#include <chrono>

#include "vypocetKostier.h"
#include "spracovanieRegularne.h"

using Hrany = std::vector<std::vector<int>>;

void SpracujCele::kontrolaHodnot(unsigned long long pocet, const Hrany& hrany) {

    if (pocet == maxK) {
        if (maxG.size() < maxDrzanych) {
            maxG.push_back(hrany);
        }
    }

    if (pocet > maxK) {
        maxK = pocet;
        maxG.clear();
        maxG.push_back(hrany);
    }
    if (pocet == minK) {
        if (minG.size() < maxDrzanych) {
            minG.push_back(hrany);
        }
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
        
        int v = stoi(vrch);
        std::string sused;  
        std::stringstream ss2(susedia);
        while (!ss2.eof()) {
            getline(ss2, sused, ' ');
            if (!sused.size()) {
                continue;
            }
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

void SpracujCele::grafyDoSuboru(unsigned long long pocet, const std::vector<Hrany>& grafy, std::ofstream& sub) {
    sub <<  grafy.size() << " " << pocet << "\n";
    
    for (const Hrany& graf : grafy) {
        sub << "[";
        bool prve = true;
        for (const std::vector<int>& hrana : graf) {
            if (prve) {
                prve = false;
            }
            else {
                sub << ", ";
            }
            sub << "(" << hrana[0] << ", " << hrana[1] << ")";
        }

        sub << "]\n";
    }


}

void SpracujCele::zapisDoSUboru(){
    suborDo << "min ";
    grafyDoSuboru(minK, minG, suborDo);
    suborDo << "max ";
    grafyDoSuboru(maxK, maxG, suborDo);

}

void SpracujCele::jedenGraf(const Riadky& graf) {
    Hrany hrany = spracujGraf(graf);
    long kostier = pocitadlo.celkovyVypocet(hrany);
    kontrolaHodnot(kostier, hrany);
}

void SpracujCele::celySubor() {
    Riadky vrcholy(n);
    unsigned long long spracovanych = 0;
    int index = 0;
    std::string riadok;
    bool zacatyGraf = false;
   
    while (std::getline(std::cin, riadok)) {
        if (riadok[0] == 'G') {
            zacatyGraf = true;
        }
        else if (!zacatyGraf || riadok.empty()) {
            continue;
        }
        
        else if (zacatyGraf){
            vrcholy.at(index) = riadok;
            index++;
            
            if (index == n) {
                jedenGraf(vrcholy);
                index = 0;
                spracovanych++;
                zacatyGraf = false;
            }
        }
    }

    zapisDoSUboru();
    suborDo.close();
    pocitadlo.koniec();

}