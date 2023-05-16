#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <algorithm>

#include "isomorphismAHU.h"

using Edges = std::vector<std::vector<int>>;
using Matica = std::vector<std::vector<int>>;

class Onete {
    int n;
    int m;
    Edges edges;

    Matica rIncT;
    Matica diag;
    Matica u;
    
    unsigned long numberOfSpanningTrees = 0;
    std::map<Tree*, int> isomorphismClassesCardinality;
    //std::vector<Tree*> triedyIzomorfizmu;
    //std::vector<int> triedyPocty;

    void fillDiag();
    void fillRIncT();
    void matrixMultiplification();

    void resetDataStructures();
    Edges evaluatePossibleTreeEdges(std::vector<int> rowIndices);
    void addNewSpanningTree(const Edges& kostra);
    void generateCandidates(int edgesRemaining, std::vector<int>& usedIndices, int indexFrom);



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

        const std::map<Tree*, int> generateAllSpanningTrees(const Edges& hrany2);
        void writeIsomorphismClassesToFile(std::string nameOfFile);
        void deleteTrees() {
            for (auto it = isomorphismClassesCardinality.begin(); it != isomorphismClassesCardinality.end(); it++) {
                delete it->first;
            }
        }
        unsigned long long getNumberOfSpanningTrees() {
            return numberOfSpanningTrees;
        }
        
};