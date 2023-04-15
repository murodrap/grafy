#include <stdio.h>
#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <fstream>
#include <sstream>

#include "generovanie.h"

using Hrany = std::vector<std::vector<int>>;

void Generator::kontrolaHodnot(unsigned long long pocet, const Hrany& hrany) {

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

void Generator::grafyDoSuboru(std::string typ, unsigned long long pocet, const std::vector<Hrany>& grafy, std::ofstream& subor) {
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

void Generator::zapisDoSUboru() {
    std::stringstream kamUkladat;
    kamUkladat << "maxMinBireg" << reg1 << "-" << n1 << "--" << reg2  << "-" << n2 << ".txt";
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

void Generator::vsetkyGrafy(std::vector<int>& ostavajuceStupne, Hrany& vybrateHrany, std::vector<int>& spojeniaDo) {
    int u = -1;
    for (int i = 0; i < n1 + n2; i++) {
        if (ostavajuceStupne[i]) {
            u = i;
            break;
        }
    }

    if (u < 0) {
        unsigned long long kostier = pocitadlo.celkovyVypocet(vybrateHrany);
        if (kostier) {
            kontrolaHodnot(kostier, vybrateHrany);
        }
        
        return;
    }
    int od;
    if (!spojeniaDo[u]) {
        od = u + 1;
    }
    else {
        od = spojeniaDo[u] + 1;
    }
    for (int v = od; v < n1 + n2; v++) {
        if (ostavajuceStupne[v]) {
            vybrateHrany.push_back({u, v});
            ostavajuceStupne[u] -= 1;
            ostavajuceStupne[v] -= 1;
            spojeniaDo[u] = v;

            vsetkyGrafy(ostavajuceStupne, vybrateHrany, spojeniaDo);

            vybrateHrany.pop_back();
            spojeniaDo[u] = od - 1;
            ostavajuceStupne[u] += 1;
            ostavajuceStupne[v] += 1;
        }

    }
    
}

void Generator::generovanie() {
    std::vector<int> stupne;
    
    stupne.reserve(n1 + n2);
    for (int i = 0; i < n1; i++) {
        stupne[i] = reg1;

    }
    for (int i = 0; i < n2; i++) {
        stupne[n1 + i] = reg2;
    }
    std::vector<int> spojenia(n1 + n2);
    Hrany h;
    vsetkyGrafy(stupne, h, spojenia);
    zapisDoSUboru();
    pocitadlo.koniec();
}