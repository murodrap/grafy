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
    std::vector<int> diagonal = std::vector<int>(n - 1);
    
    bool lineWithOneEntry = false;
    for (int i : rowIndices) {
        int number = 0;
        for (int j = 0; j < n - 1; j++) {
            if (u[i][j]) {
                usedIndices.insert(u[i][j]);
                number++;
                diagonal[j] = 1;
            } 
        }
        if (number == 1) {
            lineWithOneEntry = true;
        }
    }
    if (!lineWithOneEntry) {
        return Edges();
    }
    for (int d : diagonal) {
        if (!d) {
            return Edges();
        }
    }

    Edges spanningTree;
    spanningTree.reserve(n - 1);

    for (int edgeIndex : usedIndices) {
        spanningTree.push_back(edges[edgeIndex - 1]);
    } 
    return spanningTree;
}

void Onete::addNewSpanningTree(const Edges& spanningTree) {
    Tree* s = new Tree(spanningTree, n);
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

   isomorphismClassesCardinality[s] = 1;
}

void Onete::generateCandidates(int edgesRemaining, std::vector<int>& usedIndices, int indexFrom) {
    if (!edgesRemaining) {
        Edges spanningTree  = evaluatePossibleTreeEdges(usedIndices);
            if (spanningTree.size()) {
                addNewSpanningTree(spanningTree);
            }
        return;
    }
    int currentIndex = n - 1 - edgesRemaining;
    for (int i = indexFrom; i <= edges.size() - edgesRemaining; i++) {
        usedIndices[currentIndex] = i;
        generateCandidates(edgesRemaining - 1, usedIndices, i + 1);
    }
}

const std::map<Tree*, int> Onete::generateAllSpanningTrees(const Edges& edges2) {
    resetDataStructures();
    edges = std::move(edges2);
    fillDiag();
    fillRIncT();
    matrixMultiplification();

    std::vector<int> ind = std::vector<int>(n - 1);
    generateCandidates(n - 1, ind, 0);
    std::cout << std::endl <<  numberOfSpanningTrees << " spanning trees generated, " << isomorphismClassesCardinality.size() << " isomorphism classes" << std::endl;

    return isomorphismClassesCardinality;
    
}

void Onete::writeIsomorphismClassesToFile(std::string nameOfFIle) {
    std::ofstream file(nameOfFIle);

    file << numberOfSpanningTrees << " spanning trees, " << isomorphismClassesCardinality.size() << " isomorphism classes" << std::endl;
    for (auto it = isomorphismClassesCardinality.begin(); it != isomorphismClassesCardinality.end(); it++) {
        file << it->second << std::endl;
        file << "[";
        bool firstEdge = true;
        for (auto edge : it->first->getEdgesOfTree()) {
            if (firstEdge) {
                firstEdge = false;
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