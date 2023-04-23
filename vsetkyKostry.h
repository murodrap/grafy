#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <algorithm>

#include "izomorfizmus.h"

using Hrany = std::vector<std::vector<int>>;
using Matica = std::vector<std::vector<int>>;

class Onete {
    int n;
    int m;
    Hrany hrany;

    Matica rIncT;
    Matica diag;
    Matica u;
    
    unsigned long pocetKostrier = 0;
    std::map<Strom*, int> triedyIzomorfizmuPocty;
    //std::vector<Strom*> triedyIzomorfizmu;
    //std::vector<int> triedyPocty;

    void naplnenieDiag();
    void naplnenieRIncT();
    void nasobenieMatic();

    void vynulujDatStruktury();
    Hrany vyhodnotHrany(std::vector<int> indexyRiadkov);
    void vyhodnotIzomorfizmus(const Hrany& kostra);
    void generovanieMoznosti(int ostava, std::vector<int>& vybrateIndexy, int indexOd);



    public:
        Onete(int n2, int m2)
        : n(n2)
        , m(m2) {
            rIncT.reserve(m);
            diag.reserve(m);
            u.reserve(m);
            for (int i = 0; i < m; i++) {
                rIncT.push_back(std::vector<int>(n - 1));
                diag.push_back(std::vector<int>(m));
                u.push_back(std::vector<int>(n - 1));
            }
        }

        const std::map<Strom*, int> generovanieKostier(const Hrany& hrany2);
        void zapisDoSuboru(std::string nazpov);
        
};