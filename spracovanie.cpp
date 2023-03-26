#include <stdio.h>
#include <vector>
#include <set>
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
    kamUkladat << "maxMinBireg" << reg << "-" << n << "-" << reg2 << ".txt";
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
    Hrany najdene; 
    std::vector<int> vrchy = std::vector<int>(n);
    std::set<std::vector<int>> pouzite;
    for (auto hrana : hrany) {
        pouzite.insert(hrana);
    }
    kombinacieHran(reg2/2, 0, hrany, najdene, vrchy, pouzite);
    
}

void SpracujCele::celySubor() {
    Riadky vrcholy(n);
    long spracovanych = 0;
    int index = 0;
    std::string riadok;
    bool zacatyGraf = false;
    while (std::getline(std::cin, riadok)) {
        if (riadok[0] == 'G') {
            zacatyGraf = true;
            
            
        }
        else if (!zacatyGraf || riadok.size() == 0) {
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
                if((spracovanych % 10000) == 0) {
                    std::cout << spracovanych << "\n";
                }
            }
        }
    }

    zapisDoSUboru();

}

void SpracujCele::kombinacieHran(int ostavaDlzky, int odIndexu, const Hrany& hrany, Hrany& zatialVybrate, std::vector<int>& zahrnuteVrchy, std::set<std::vector<int>>& vysledneHrany) {
    
    if (!ostavaDlzky) {
        Hrany hranyGrafu = Hrany((n*reg + reg2) / 2);
        copy(vysledneHrany.begin(), vysledneHrany.end(), hranyGrafu.begin());
        unsigned long long kostrier = VypocetKostier::celkovyVypocet(hranyGrafu, 0, n+1);
        kontrolaHodnot(kostrier, hranyGrafu);
        return;
    }
    if (ostavaDlzky > hrany.size() - odIndexu) {
        return;
    }
    for (int i = odIndexu; i <= hrany.size() - ostavaDlzky; i++) {
        int v = hrany[i][0];
        int u = hrany[i][1];
       
        if (vznikneNasHrana(u, v, zahrnuteVrchy)) {
                continue;
        }
        
        zahrnuteVrchy[u] = 1;
        zahrnuteVrchy[v] = 1;
        zatialVybrate.push_back(hrany[i]);
        vysledneHrany.erase(hrany[i]);
        std::vector<int> h1 = {u, n};
        std::vector<int> h2 = {v, n};
        vysledneHrany.insert(h1);
        vysledneHrany.insert(h2);
        kombinacieHran(ostavaDlzky - 1, i+1, hrany, zatialVybrate, zahrnuteVrchy, vysledneHrany);
        zatialVybrate.pop_back();
        vysledneHrany.insert(hrany[i]);
        vysledneHrany.erase(h1);
        vysledneHrany.erase(h2);
        zahrnuteVrchy[u] = 0;
        zahrnuteVrchy[v] = 0;
    }
    return;
}

bool SpracujCele::vznikneNasHrana(int u, int v, std::vector<int>& zahrnuteVrchy){
    if (zahrnuteVrchy[u]) {
            return true;
        }
    return zahrnuteVrchy[v];
}