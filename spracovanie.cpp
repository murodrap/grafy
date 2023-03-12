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

#include "VypocetKostier.h"
#include "spracovanie.h"

using Hrany = std::vector<std::vector<int>>;

// export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/terezia/oneTbbInstallation/lib

void SpracujCele::kontrolaHodnot(unsigned long long pocet, const Hrany& hrany) {
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

void SpracujCele::grafyDoSuboru(std::string typ, unsigned long long pocet, const std::vector<Hrany>& grafy, std::ofstream& subor) {
    subor << typ << " " << grafy.size() << " " << pocet << "\n";
        
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

void SpracujCele::grafyDoSuboru(std::string typ, unsigned long long pocet, const std::vector<std::string>& grafy, std::ofstream& subor) {
    subor << typ << " " << grafy.size() << " " << pocet << "\n";
        
    for (const std::string& graf: grafy) {
        subor << graf << std::endl;
    }

}

void SpracujCele::zapisDoSUboru() {
    std::stringstream kamUkladat;
    kamUkladat << "out-" << suborZ << ".txt";
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

std::pair<unsigned long long, const std::vector<std::string>> SpracujCele::nacitanieVyslPreTyp(std::ifstream& subor) {
    std::string riadok;
    std::getline(subor, riadok);
    std::istringstream iss(riadok);
    std::string typ;
    int pocetG;
    unsigned long long kostier;
    iss >> typ;
    iss >> pocetG;
    iss >> kostier;
    std::vector<std::string> grafy = std::vector<std::string>(pocetG);
    for (int j = 0; j < pocetG; j++) {
        std::getline(subor, riadok);
        grafy[j] = std::move(riadok);
    }
    return std::make_pair(kostier, std::move(grafy));
}


void SpracujCele::vyhodnotenieVysledkovSubory() {
    std::vector<std::string> minZoSuborov;
    std::vector<std::string> maxZoSuborov;
    std::ifstream subor;
    for (int i = 1; i <= pocetSuborov; i++) {
        std::stringstream meno;
        meno << suborZ << "-" << i << ".txt";
        subor.open(meno.str());
        if (!subor.is_open()) {
            std::cout << "nepodarilo sa otvorit subor " << meno.str() << std::endl;
            return;
        }

        std::pair<unsigned long long, const std::vector<std::string>> vyslMin = nacitanieVyslPreTyp(subor);
        unsigned long long kostier = vyslMin.first;
        const std::vector<std::string>& hrany = vyslMin.second;
        
        if (kostier == minK) {
            for (const std::string& g : hrany) {
                minZoSuborov.push_back(g);
            }
        }
        
        else if (kostier < minK) {
            minK = kostier;
            minZoSuborov.clear();
            for (const std::string& g : hrany) {
                minZoSuborov.push_back(g);
            }
        }

        std::pair<unsigned long long, const std::vector<std::string>> vyslMax = nacitanieVyslPreTyp(subor);
        kostier = vyslMax.first;
        const std::vector<std::string>& hrany2 = vyslMax.second;
        if (kostier == maxK) {
            for (const std::string & g : hrany2) {
                maxZoSuborov.push_back(g);
            }
        }
        else if (kostier > maxK) {
            maxK = kostier;
            maxZoSuborov.clear();
            for (const std::string & g : hrany2) {
                maxZoSuborov.push_back(g);
            }
        }
        subor.close();

        
    }
    std::stringstream kamUkladat;
    kamUkladat << "maxMinReg" << reg << "-" << n << "-" << pocetSuborov << ".txt";
    std::ofstream subor2;
    subor2.open (kamUkladat.str());
    grafyDoSuboru("min", minK, minZoSuborov, subor2);
    grafyDoSuboru("max", maxK, maxZoSuborov, subor2);
    subor2.close();
}


void SpracujCele::jedenGraf(const Riadky& graf) {
    Hrany hrany = spracujGraf(graf);
    long kostrier = VypocetKostier::celkovyVypocet(hrany, reg, n);
    kontrolaHodnot(kostrier, hrany);
}

void SpracujCele::celySubor() {
    std::ifstream subor;
    subor.open(suborZ);
    if (!subor.is_open()) {
        std::cout << "nepodarilo sa otvorit a spracovat subor " << suborZ << std::endl;
        exit(1);
    }

    Riadky vrcholy(n);
    unsigned long long spracovanych = 0;
    int index = 0;
    std::string riadok;
    bool zacatyGraf = false;
    while (std::getline(subor, riadok)) {
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
                //if((spracovanych % 10000) == 0) {
                //    std::cout << spracovanych << "\n";
                //}
            }
        }
    }

    zapisDoSUboru();

}