#include <stdio.h>
#include <vector>
#include <string>
#include <regex>
#include <bits/stdc++.h>
#include <string.h>

#include "vypocetKostier.h"
#include "vseobecne.h"
#include "izomorfizmus.h"


bool VseobecneFunkcie::havelHakimi(int n1, int k1, int n2, int k2) {
    std::vector<int> stupne;
    for (int i  = 0; i < n1; i++) {
        stupne.push_back(k1);
    }
    for (int i  = 0; i < n2; i++) {
        stupne.push_back(k2);
    }
    std::sort(stupne.begin(), stupne.end(), std::greater<int>());

    while (true){
        if (stupne[0] == 0) {
            break;
        }
        
        for (int i = 1; i <= stupne[0]; i++) {
            if (stupne[i] == 0) {
                return false;
            }
            stupne[i] -= 1;
        }
        stupne[0] = 0;
        std::sort(stupne.begin(), stupne.end(), std::greater<int>());
    }
    return true;
}

bool VseobecneFunkcie::existujeGraf(int n1, int k1, int n2, int k2){
    if (k1 > n1 + n2 || k2 > n1 + n2) {
        std::cout << "nie je mozne vytvorit graf bez nasobnych hran" << std::endl;
        return false;
    }
    if ((n1 * k1 + n2 * k2) % 2) {
        std::cout << "neparny sucet stupnov" << std::endl;
        return false;
    }
    if (!havelHakimi(n1, k1, n2, k2)) {
        std::cout << "nesedi havel hakimi" << std::endl;
        return false;
    }
    return true;
}


Hrany VseobecneFunkcie::stringNaHrany(std::string& zoznamHran) {
    Hrany hrany;

    std::string znaky;

    std::regex hranaRegex("[0-9]+, [0-9]+");
    std::regex vrcholyRegex("([0-9]+), ([0-9]+)");
    std::smatch hranyNajdene;
    std::smatch vrcholyNajdene;

    while (std::regex_search(zoznamHran, hranyNajdene, hranaRegex)) {
   
        std::string vr = hranyNajdene[0];
        std::regex_search(vr, vrcholyNajdene, vrcholyRegex);
        std::string v = vrcholyNajdene[1];
        std::string u = vrcholyNajdene[2];
        hrany.push_back({std::stoi(v), std::stoi(u)});
        zoznamHran = hranyNajdene.suffix();
    }

    return hrany;
}

AdjList VseobecneFunkcie::stringNaAdjList(std::string& zoznamHran, int n) {
    AdjList adjList;
    for (int v = 0; v < n; v++) {
        adjList[v] = std::vector<int>();
    }

    std::string znaky;

    std::regex hranaRegex("[0-9]+, [0-9]+");
    std::regex vrcholyRegex("([0-9]+), ([0-9]+)");
    std::smatch hranyNajdene;
    std::smatch vrcholyNajdene;

    while (std::regex_search(zoznamHran, hranyNajdene, hranaRegex)) {
        std::string vr = hranyNajdene[0];
        std::regex_search(vr, vrcholyNajdene, vrcholyRegex);
        int v = std::stoi(vrcholyNajdene[1]);
        int u = std::stoi(vrcholyNajdene[2]);
        adjList[v].push_back(u);
        adjList[u].push_back(v);
        zoznamHran = hranyNajdene.suffix();
    }

    return adjList;

}

bool VseobecneFunkcie::izomorfneGrafy(std::string& g1, int n1, std::string& g2, int n2) {
    const AdjList adj1 = stringNaAdjList(g1, n1);
    const AdjList adj2 = stringNaAdjList(g2, n2);
    return izomorfneGrafy(adj1, n1, adj2, n2);
}

bool VseobecneFunkcie::izomorfneGrafy(const AdjList& g1, int n1, const AdjList& g2, int n2) {
    Strom* graf1 = new Strom(g1, n1);
    Strom* graf2 = new Strom(g2, n2);
    bool vysl = graf1->suIzomorfne(graf2);
    delete graf1;
    delete graf2;
    return vysl;
}

