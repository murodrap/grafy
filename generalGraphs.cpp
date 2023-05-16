#include <stdio.h>
#include <vector>
#include <string>
#include <regex>
#include <bits/stdc++.h>
#include <string.h>

#include "spanningTreeCounting.h"
#include "generalGraphs.h"
#include "isomorphismAHU.h"


bool GeneralFunctionsForGraphs::havelHakimi(int n1, int k1, int n2, int k2) {
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

bool GeneralFunctionsForGraphs::checkGraphExistence(int n1, int k1, int n2, int k2){
    if (k1 > n1 + n2 || k2 > n1 + n2) {
        std::cout << "nie je mozne vytvorit graph bez nasobnych hran" << std::endl;
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


Edges GeneralFunctionsForGraphs::stringToEdges(std::string& listOfEdges) {
    Edges edges;

    std::string znaky;

    std::regex hranaRegex("[0-9]+, [0-9]+");
    std::regex vrcholyRegex("([0-9]+), ([0-9]+)");
    std::smatch hranyNajdene;
    std::smatch vrcholyNajdene;

    while (std::regex_search(listOfEdges, hranyNajdene, hranaRegex)) {
   
        std::string vr = hranyNajdene[0];
        std::regex_search(vr, vrcholyNajdene, vrcholyRegex);
        std::string v = vrcholyNajdene[1];
        std::string u = vrcholyNajdene[2];
        int v1 = std::stoi(v);
        int u1 = std::stoi(u);
        if (v1 < u1) {
            edges.push_back({v1, u1});
        }
        else {
           edges.push_back({u1, v1}); 
        }
        listOfEdges = hranyNajdene.suffix();
    }

    return edges;
}

AdjList GeneralFunctionsForGraphs::stringToAdjList(std::string& listOfEdges, int n) {
    AdjList adjList;
    for (int v = 0; v < n; v++) {
        adjList[v] = std::vector<int>();
    }

    std::string znaky;

    std::regex hranaRegex("[0-9]+, [0-9]+");
    std::regex vrcholyRegex("([0-9]+), ([0-9]+)");
    std::smatch hranyNajdene;
    std::smatch vrcholyNajdene;

    while (std::regex_search(listOfEdges, hranyNajdene, hranaRegex)) {
        std::string vr = hranyNajdene[0];
        std::regex_search(vr, vrcholyNajdene, vrcholyRegex);
        int v = std::stoi(vrcholyNajdene[1]);
        int u = std::stoi(vrcholyNajdene[2]);
        adjList[v].push_back(u);
        adjList[u].push_back(v);
        listOfEdges = hranyNajdene.suffix();
    }

    return adjList;

}

bool GeneralFunctionsForGraphs::isomorphicGraphs(std::string& g1, int n1, std::string& g2, int n2) {
    const AdjList adj1 = stringToAdjList(g1, n1);
    const AdjList adj2 = stringToAdjList(g2, n2);
    return isomorphicGraphs(adj1, n1, adj2, n2);
}

bool GeneralFunctionsForGraphs::isomorphicGraphs(const AdjList& g1, int n1, const AdjList& g2, int n2) {
    Tree* graph1 = new Tree(g1, n1);
    Tree* graf2 = new Tree(g2, n2);
    bool vysl = graph1->checkIsomorphism(graf2);
    delete graph1;
    delete graf2;
    return vysl;
}

Edges GeneralFunctionsForGraphs::spanningTreeBFS(const AdjList& graph, int n) {
    std::set<int> navstiveneVrchy = {0};
    std::set<int> naPrejdenie = {0};
    Edges hranyKostry;

    while (naPrejdenie.size()) {
        std::set<int> noveNaPrejdenie;
        for (int u : naPrejdenie) {
            for (int v : graph.find(u)->second) {
                if (navstiveneVrchy.find(v) == navstiveneVrchy.end()) {
                    navstiveneVrchy.insert(v);
                    std::vector<int> edge ={u, v};
                    if (v < u) {
                        edge = {v, u};
                    }
                    hranyKostry.push_back(edge);
                    noveNaPrejdenie.insert(v);
                }
            }
            
        }
        naPrejdenie.clear();
        naPrejdenie.insert(noveNaPrejdenie.begin(), noveNaPrejdenie.end());
        noveNaPrejdenie.clear();
    }

    return hranyKostry;
}

void GeneralFunctionsForGraphs::printGraph(const Edges& graph) {
        std::cout << "[";
        bool prve = true;
        for (auto edge : graph) {
            if (prve) {
                prve = false;
            }
            else {
                std::cout << ", ";
            }
            std::cout  << "(" << edge[0] << ", " << edge[1] << ")";
        }
        std::cout << "]" << std::endl;
}

void GeneralFunctionsForGraphs::compareUnlabeledSpanningTrees(std::string& g1, int n1, std::string& g2, int n2) {
    auto edges1 = GeneralFunctionsForGraphs::stringToEdges(g1);
    auto hrany2 = GeneralFunctionsForGraphs::stringToEdges(g2);
    std::cout << "first graph: ";
    const std::map<Tree*, int> triedyKostier1 = GeneralFunctionsForGraphs::generateAllSpanningTrees(edges1, n1, "kostryG1.txt");
    std::cout << "second graph: ";
    const std::map<Tree*, int> triedyKostier2 = GeneralFunctionsForGraphs::generateAllSpanningTrees(hrany2, n2, "kostryG2.txt");
    std::cout << "unlabeled spanning trees present in both graphs:" << std::endl;

    unsigned long long spolocne = 0;
    for (auto it1 = triedyKostier1.begin(); it1 != triedyKostier1.end(); it1++) {
        for (auto it2 = triedyKostier2.begin(); it2 != triedyKostier2.end(); it2++) {
            if (it1->first->checkIsomorphism(it2->first)) {
                //std::cout << "izom\n";
                spolocne++;
                GeneralFunctionsForGraphs::printGraph(it1->first->getEdgesOfTree());
            }
        }
    }

    for (auto it = triedyKostier1.begin(); it != triedyKostier1.end(); it++) {
        delete it->first;
    }
    for (auto it = triedyKostier2.begin(); it != triedyKostier2.end(); it++) {
        delete it->first;
    }
    std::cout << std::endl << spolocne << " total" << std::endl;
}

