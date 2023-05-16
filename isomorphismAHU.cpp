#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <climits>
#include <string>
#include <sstream>

#include <bits/stdc++.h>

#include "isomorphismAHU.h"


std::string Tree::codeOfTreeAHU(int root) {
    visitedVertices.clear();
    visitedVertices.insert(root);
    return codeOfVertexAHU(root);

}

std::pair<int, std::vector<int>> Tree::mostDistantVertex(int v) {
    std::vector<int> c = {v};
    std::vector<std::pair<int, std::vector<int>>> naPrejdenie = {std::make_pair(v, c)};
    std::vector<std::pair<int, std::vector<int>>> predchadzajuce;
    
    visitedVertices.clear();
    visitedVertices.insert(v);
    
    while (!naPrejdenie.empty()) {
        std::vector<std::pair<int, std::vector<int>>> nove;
        for (auto vrchCesta : naPrejdenie) {
            
            int u = vrchCesta.first;

            std::vector<int>& cesta = vrchCesta.second;
            
            for (int potomok : graph.find(u)->second) {
                if (visitedVertices.find(potomok) == visitedVertices.end()) {
                    visitedVertices.insert(potomok);

                    std::vector<int> cestaRozsirena = cesta;
                    cestaRozsirena.push_back(potomok);
                    nove.push_back({potomok,cestaRozsirena});
                }
            }
        }
        
        predchadzajuce = std::move(naPrejdenie);
        naPrejdenie = std::move(nove);
    }
    return predchadzajuce[0];
}

std::vector<int> Tree::rootsSearch() {

    int x = 0;
    std::pair<int, std::vector<int>> v1Cesta1 = mostDistantVertex(x);
    std::pair<int, std::vector<int>> v2Cesta2 = mostDistantVertex(v1Cesta1.first);
    const std::vector<int>& cesta2 = v2Cesta2.second;
    std::vector<int> getRoots = {cesta2[cesta2.size()/2]};
    
    if (!(cesta2.size() % 2)) {
        getRoots.push_back(cesta2[cesta2.size()/2 - 1]);
    }
    return getRoots;

}

std::string Tree::codeOfVertexAHU(int vertex) {

    std::vector<std::string> stredKodu;
    for (int potomok : graph.find(vertex)->second) {
        if (visitedVertices.find(potomok) == visitedVertices.end()) {
            visitedVertices.insert(potomok);
            stredKodu.emplace_back(codeOfVertexAHU(potomok));
        }
    }
    std::sort(stredKodu.begin(), stredKodu.end(), std::greater<std::string>());
    std::stringstream kod;
    kod << "0";
    for (const std::string& kodPotomka : stredKodu) {
        kod << kodPotomka;
    }

    kod << "1";

    return kod.str();

}


bool Tree::checkIsomorphism(Tree* tree2) {
    if (tree2->getNumberOfVertices() != getNumberOfVertices()) {
        return false;
    }

    if (getRoots().size() != tree2->getRoots().size()) {
        return false;
    }
    for (auto kod1 : getAHUcodes()) {
        for (auto kod2 : tree2->getAHUcodes()) {
            if (kod1 == kod2) {
                return true;
            }
        }
    }

    return false;
}