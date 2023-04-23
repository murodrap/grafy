#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "vsetkyKostry.h"
#include "izomorfizmus.h"

using Hrany = std::vector<std::vector<int>>;
using Matica = std::vector<std::vector<int>>;

void Onete::naplnenieDiag() {
    for (int i = 0; i < m; i++) {
        diag[i][i] = i+1;
    }

    /*
    std::cout << std::endl;
    for (int i = 0; i < diag.size(); i++) {
        for (int j  = 0; j < diag[0].size(); j++) {
            std::cout << diag[i][j] << " ";
        }
        std::cout << std::endl;
    }
    */
}


void Onete::naplnenieRIncT() {
    for (int r = 0; r < m; r++) {
        int v1 = hrany[r][0];
        int v2 = hrany[r][1];
        rIncT[r][v1] = 1;
        if (v2 < n - 1) {
            rIncT[r][v2] = 1;
        }
    }   

    /*
    std::cout << std::endl;
    for (int i = 0; i < rIncT.size(); i++) {
        for (int j  = 0; j < rIncT[0].size(); j++) {
            std::cout << rIncT[i][j] << " ";
        }
        std::cout << std::endl;
    }
    */
}

void Onete::nasobenieMatic() {
    for (int i = 0; i < m; i++) {
        for (int j  = 0; j < n - 1; j++) {
            int x = 0;
            for (int xi = 0; xi < m; xi++) {
                x += diag[i][xi] * rIncT[xi][j];
            }
            u[i][j] = x;
        }
    }
    /*
    std::cout << std::endl;
    for (int i = 0; i < u.size(); i++) {
        for (int j  = 0; j < u[0].size(); j++) {
            std::cout << u[i][j] << " ";
        }
        std::cout << std::endl;
    }
    */
}

void Onete::vynulujDatStruktury() {
    for (int r = 0; r < m; r++) {
        std::fill(rIncT[r].begin(), rIncT[r].end(), 0);
        std::fill(u[r].begin(), u[r].end(), 0);
    }
    pocetKostrier = 0;
    triedyIzomorfizmuPocty.clear();
    for (auto it = triedyIzomorfizmuPocty.begin(); it != triedyIzomorfizmuPocty.end(); it++) {
        delete it->first;
    }
    triedyIzomorfizmuPocty.clear();
    
}



Hrany Onete::vyhodnotHrany(std::vector<int> indexyRiadkov) {
    std::set<int> vybrateIndexy;
    std::vector<int> diagonala = std::vector<int>(n - 1);
    
    bool vyhovujuciRiadok = false;
    for (int i : indexyRiadkov) {
        int pocet = 0;
        for (int j = 0; j < n - 1; j++) {
            if (u[i][j]) {
                vybrateIndexy.insert(u[i][j]);
                pocet++;
                diagonala[j] = 1;
            } 
        }
        if (pocet == 1) {
            vyhovujuciRiadok = true;
        }
    }
    if (!vyhovujuciRiadok) {
        return Hrany();
    }
    for (int nenulove : diagonala) {
        if (!nenulove) {
            return Hrany();
        }
    }

    Hrany kostra;
    kostra.reserve(n - 1);

    for (int indexHrany : vybrateIndexy) {
        kostra.push_back(hrany[indexHrany - 1]);
    } 
    return kostra;
}

void Onete::vyhodnotIzomorfizmus(const Hrany& kostra) {
    Strom* s = new Strom(kostra, n);
    if (s->kodyAHU()[0].size() != n * 2) {
        delete s;
        return;
    }
    pocetKostrier++;
    
    for (auto it = triedyIzomorfizmuPocty.begin(); it != triedyIzomorfizmuPocty.end(); it++) {
        if (it->first->suIzomorfne(s)) {
            it->second++;
            delete s;
            return;
        }
    }
    /*
    for (int i = 0; i < triedyIzomorfizmu.size(); i++) {
        if (triedyIzomorfizmu[i]->suIzomorfne(s)) {
            triedyPocty[i]++;
            delete s;
            return;
        }
    }
    */
   triedyIzomorfizmuPocty[s] = 1;
//triedyIzomorfizmu.emplace_back(s);
  //  triedyPocty.push_back(1);
}

void Onete::generovanieMoznosti(int ostava, std::vector<int>& vybrateIndexy, int indexOd) {
    if (!ostava) {
        Hrany kostra  = vyhodnotHrany(vybrateIndexy);
            if (kostra.size()) {
                vyhodnotIzomorfizmus(kostra);
            }
        return;
    }
    int sucInd = n - 1 - ostava;
    for (int i = indexOd; i <= hrany.size() - ostava; i++) {
        vybrateIndexy[sucInd] = i;
        generovanieMoznosti(ostava - 1, vybrateIndexy, i + 1);
    }
}

const std::map<Strom*, int> Onete::generovanieKostier(const Hrany& hrany2) {
    vynulujDatStruktury();
    hrany = std::move(hrany2);
    naplnenieDiag();
    naplnenieRIncT();
    nasobenieMatic();

    std::vector<int> ind = std::vector<int>(n - 1);
    generovanieMoznosti(n - 1, ind, 0);
    std::cout << std::endl << "bolo vygenerovanych "<< pocetKostrier << " kostier, " << triedyIzomorfizmuPocty.size() << " tried" << std::endl;

    return triedyIzomorfizmuPocty;
    
}

void Onete::zapisDoSuboru(std::string nazov) {
    std::ofstream subor(nazov);

    subor << pocetKostrier << " kostier, " << triedyIzomorfizmuPocty.size() << " tried" << std::endl;
    for (auto it = triedyIzomorfizmuPocty.begin(); it != triedyIzomorfizmuPocty.end(); it++) {
        subor << it->second << std::endl;
        subor << "[";
        bool prve = true;
        for (auto hrana : it->first->hranyStromu()) {
            if (prve) {
                prve = false;
            }
            else {
                subor << ", ";
            }
            subor  << "(" << hrana[0] << ", " << hrana[1] << ")";
        }
        subor << "]" << std::endl;
    }
    subor.close();
}