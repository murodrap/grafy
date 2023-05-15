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

#include "vypocetKostier.h"
#include "spracovanieBiregularne.h"

using Hrany = std::vector<std::vector<int>>;
using Riadky = std::vector<std::string>;


void SpracujCeleBiregularne::kombinacieHran(int ostavaDlzky, int odIndexu, const Hrany& hrany, Hrany& zatialVybrate, std::vector<int>& zahrnuteVrchy, std::set<std::vector<int>>& vysledneHrany) {
    
    if (!ostavaDlzky) {
        Hrany hranyGrafu = Hrany((n*reg + reg2) / 2);
        copy(vysledneHrany.begin(), vysledneHrany.end(), hranyGrafu.begin());
        long long kostrier = pocitadlo.celkovyVypocet(hranyGrafu);
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

bool SpracujCeleBiregularne::vznikneNasHrana(int u, int v, std::vector<int>& zahrnuteVrchy){
    if (zahrnuteVrchy[u]) {
            return true;
        }
    return zahrnuteVrchy[v];
}

void SpracujCeleBiregularne::jedenGraf(const Riadky& graf) {
    Hrany hrany = spracujGraf(graf);
    Hrany najdene; 
    std::vector<int> vrchy = std::vector<int>(n);
    std::set<std::vector<int>> pouzite;
    for (auto hrana : hrany) {
        pouzite.insert(hrana);
    }
    kombinacieHran(reg2/2, 0, hrany, najdene, vrchy, pouzite);
    
}

