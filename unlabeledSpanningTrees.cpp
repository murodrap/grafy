#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "unlabeledSpanningTrees.h"
#include "isomorphismAHU.h"

using Edges = std::vector<std::vector<int>>;
using Matica = std::vector<std::vector<int>>;

void Onete::fillDiag() {
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


void Onete::fillRIncT() {
    for (int r = 0; r < m; r++) {
        int v1 = edges[r][0];
        int v2 = edges[r][1];
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

void Onete::matrixMultiplification() {
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

void Onete::resetDataStructures() {
    for (int r = 0; r < m; r++) {
        std::fill(rIncT[r].begin(), rIncT[r].end(), 0);
        std::fill(u[r].begin(), u[r].end(), 0);
    }
    numberOfSpanningTrees = 0;
    deleteTrees();
    isomorphismClassesCardinality.clear();
    
}



Edges Onete::evaluatePossibleTreeEdges(std::vector<int> rowIndices) {
    std::set<int> usedIndices;
    std::vector<int> diagonala = std::vector<int>(n - 1);
    
    bool vyhovujuciRiadok = false;
    for (int i : rowIndices) {
        int number = 0;
        for (int j = 0; j < n - 1; j++) {
            if (u[i][j]) {
                usedIndices.insert(u[i][j]);
                number++;
                diagonala[j] = 1;
            } 
        }
        if (number == 1) {
            vyhovujuciRiadok = true;
        }
    }
    if (!vyhovujuciRiadok) {
        return Edges();
    }
    for (int nenulove : diagonala) {
        if (!nenulove) {
            return Edges();
        }
    }

    Edges kostra;
    kostra.reserve(n - 1);

    for (int indexHrany : usedIndices) {
        kostra.push_back(edges[indexHrany - 1]);
    } 
    return kostra;
}

void Onete::addNewSpanningTree(const Edges& kostra) {
    Tree* s = new Tree(kostra, n);
    if (s->getAHUcodes()[0].size() != n * 2) {
        delete s;
        return;
    }
    numberOfSpanningTrees++;
    
    for (auto it = isomorphismClassesCardinality.begin(); it != isomorphismClassesCardinality.end(); it++) {
        if (it->first->checkIsomorphism(s)) {
            it->second++;
            delete s;
            return;
        }
    }
    /*
    for (int i = 0; i < triedyIzomorfizmu.size(); i++) {
        if (triedyIzomorfizmu[i]->checkIsomorphism(s)) {
            triedyPocty[i]++;
            delete s;
            return;
        }
    }
    */
   isomorphismClassesCardinality[s] = 1;
//triedyIzomorfizmu.emplace_back(s);
  //  triedyPocty.push_back(1);
}

void Onete::generateCandidates(int edgesRemaining, std::vector<int>& usedIndices, int indexFrom) {
    if (!edgesRemaining) {
        Edges kostra  = evaluatePossibleTreeEdges(usedIndices);
            if (kostra.size()) {
                addNewSpanningTree(kostra);
            }
        return;
    }
    int sucInd = n - 1 - edgesRemaining;
    for (int i = indexFrom; i <= edges.size() - edgesRemaining; i++) {
        usedIndices[sucInd] = i;
        generateCandidates(edgesRemaining - 1, usedIndices, i + 1);
    }
}

const std::map<Tree*, int> Onete::generateAllSpanningTrees(const Edges& hrany2) {
    resetDataStructures();
    edges = std::move(hrany2);
    fillDiag();
    fillRIncT();
    matrixMultiplification();

    std::vector<int> ind = std::vector<int>(n - 1);
    generateCandidates(n - 1, ind, 0);
    std::cout << std::endl <<  numberOfSpanningTrees << " spanning trees generated, " << isomorphismClassesCardinality.size() << " isomorphism classes" << std::endl;

    return isomorphismClassesCardinality;
    
}

void Onete::writeIsomorphismClassesToFile(std::string nazov) {
    std::ofstream file(nazov);

    file << numberOfSpanningTrees << " spanning trees, " << isomorphismClassesCardinality.size() << " isomorphism classes" << std::endl;
    for (auto it = isomorphismClassesCardinality.begin(); it != isomorphismClassesCardinality.end(); it++) {
        file << it->second << std::endl;
        file << "[";
        bool prve = true;
        for (auto edge : it->first->getEdgesOfTree()) {
            if (prve) {
                prve = false;
            }
            else {
                file << ", ";
            }
            file  << "(" << edge[0] << ", " << edge[1] << ")";
        }
        file << "]" << std::endl;
    }
    file.close();
}