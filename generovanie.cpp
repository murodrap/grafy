#include <stdio.h>
#include <iostream>
#include <vector>
#include <climits>
#include <string>
#include <fstream>
#include <sstream>

#include "generovanie.h"

using Edges = std::vector<std::vector<int>>;

void Generator::updateValues(unsigned long long number, const Edges& edges) {

    if (number == maxK) {
        maxG.push_back(edges);
    }

    if (number > maxK) {
        maxK = number;
        maxG.clear();
        maxG.push_back(edges);
    }
    if (number == minK) {
        minG.push_back(edges);
    }

    if (number < minK) {
        minK = number;
        minG.clear();
        minG.push_back(edges);
    }
}

void Generator::graphsToFile(std::string type, unsigned long long number, const std::vector<Edges>& graphs, std::ofstream& file) {
    file << type << " " << number << "\n";
        
    for (const Edges& graph : graphs) {
        file << "[";
        bool prve = true;
        for (const std::vector<int>& edge : graph) {
            if (prve) {
                prve = false;
            }
            else {
                file << ", ";
            }
            file << "(" << edge[0] << ", " << edge[1] << ")";
        }

        file << "]\n";
    }

}

void Generator::writeToFile() {
    std::stringstream kamUkladat;
    kamUkladat << "maxMinBireg" << reg1 << "-" << n1 << "--" << reg2  << "-" << n2 << ".txt";
    std::ofstream file;
    file.open (kamUkladat.str());
    if (file.is_open()) {
        graphsToFile("min", minK, minG, file);
        graphsToFile("max", maxK, maxG, file);

        file.close();
    }
    else {
        std::cout << "Unepodarilo sa vytvorit file a zapisat donho vysledky";
    }
}

void Generator::vsetkyGrafy(std::vector<int>& ostavajuceStupne, Edges& vybrateHrany, std::vector<int>& spojeniaDo) {
    int u = -1;
    for (int i = 0; i < n1 + n2; i++) {
        if (ostavajuceStupne[i]) {
            u = i;
            break;
        }
    }

    if (u < 0) {
        unsigned long long kostier = counter.countForGraph(vybrateHrany);
        if (kostier) {
            updateValues(kostier, vybrateHrany);
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
    Edges h;
    vsetkyGrafy(stupne, h, spojenia);
    writeToFile();
    counter.koniec();
}