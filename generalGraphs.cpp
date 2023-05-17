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
    std::vector<int> degrees;
    for (int i  = 0; i < n1; i++) {
        degrees.push_back(k1);
    }
    for (int i  = 0; i < n2; i++) {
        degrees.push_back(k2);
    }
    std::sort(degrees.begin(), degrees.end(), std::greater<int>());

    while (true){
        if (degrees[0] == 0) {
            break;
        }
        
        for (int i = 1; i <= degrees[0]; i++) {
            if (degrees[i] == 0) {
                return false;
            }
            degrees[i] -= 1;
        }
        degrees[0] = 0;
        std::sort(degrees.begin(), degrees.end(), std::greater<int>());
    }
    return true;
}

bool GeneralFunctionsForGraphs::checkGraphExistence(int n1, int k1, int n2, int k2){
    if (k1 > n1 + n2 || k2 > n1 + n2) {
        std::cout << "It is not possible to create a graph without multiple edges" << std::endl;
        return false;
    }
    if ((n1 * k1 + n2 * k2) % 2) {
        std::cout << "Odd sum of degrees" << std::endl;
        return false;
    }
    if (!havelHakimi(n1, k1, n2, k2)) {
        std::cout << "It is not possible to construct a graph for this combination of n1, k1, n2 and k2" << std::endl;
        return false;
    }
    return true;
}


Edges GeneralFunctionsForGraphs::stringToEdges(std::string& listOfEdges) {
    Edges edges;
    std::regex edgeRegex("[0-9]+, [0-9]+");
    std::regex verticesRegex("([0-9]+), ([0-9]+)");
    std::smatch edgesFromRegex;
    std::smatch verticesFromRegex;

    while (std::regex_search(listOfEdges, edgesFromRegex, edgeRegex)) {
   
        std::string vr = edgesFromRegex[0];
        std::regex_search(vr, verticesFromRegex, verticesRegex);
        std::string v = verticesFromRegex[1];
        std::string u = verticesFromRegex[2];
        int v1 = std::stoi(v);
        int u1 = std::stoi(u);
        if (v1 < u1) {
            edges.push_back({v1, u1});
        }
        else {
           edges.push_back({u1, v1}); 
        }
        listOfEdges = verticesFromRegex.suffix();
    }

    return edges;
}

AdjList GeneralFunctionsForGraphs::stringToAdjList(std::string& listOfEdges, int n) {
    AdjList adjList;
    for (int v = 0; v < n; v++) {
        adjList[v] = std::vector<int>();
    }

    std::regex edgeRegex("[0-9]+, [0-9]+");
    std::regex verticesRegex("([0-9]+), ([0-9]+)");
    std::smatch edgesFromRegex;
    std::smatch verticesFromRegex;

    while (std::regex_search(listOfEdges, edgesFromRegex, edgeRegex)) {
        std::string vr = edgesFromRegex[0];
        std::regex_search(vr, verticesFromRegex, verticesRegex);
        int v = std::stoi(verticesFromRegex[1]);
        int u = std::stoi(verticesFromRegex[2]);
        adjList[v].push_back(u);
        adjList[u].push_back(v);
        listOfEdges = edgesFromRegex.suffix();
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
    Tree* graph2 = new Tree(g2, n2);
    bool result = graph1->checkIsomorphism(graph2);
    delete graph1;
    delete graph2;
    return result;
}

Edges GeneralFunctionsForGraphs::spanningTreeBFS(const AdjList& graph, int n) {
    std::set<int> visitedVertices = {0};
    std::set<int> verticesToVisit = {0};
    Edges spanningTreeEdges;

    while (verticesToVisit.size()) {
        std::set<int> newVerticesToVisit;
        for (int u : verticesToVisit) {
            for (int v : graph.find(u)->second) {
                if (visitedVertices.find(v) == visitedVertices.end()) {
                    visitedVertices.insert(v);
                    std::vector<int> edge ={u, v};
                    if (v < u) {
                        edge = {v, u};
                    }
                    spanningTreeEdges.push_back(edge);
                    newVerticesToVisit.insert(v);
                }
            }
            
        }
        verticesToVisit.clear();
        verticesToVisit.insert(newVerticesToVisit.begin(), newVerticesToVisit.end());
        newVerticesToVisit.clear();
    }

    return spanningTreeEdges;
}

void GeneralFunctionsForGraphs::printGraph(const Edges& graph) {
        std::cout << "[";
        bool firstEdge = true;
        for (auto edge : graph) {
            if (firstEdge) {
                firstEdge = false;
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
    auto edges2 = GeneralFunctionsForGraphs::stringToEdges(g2);
    std::cout << "first graph: ";
    const std::map<Tree*, int> isomorphismClasses1 = GeneralFunctionsForGraphs::generateAllSpanningTrees(edges1, n1, "kostryG1.txt");
    std::cout << "second graph: ";
    const std::map<Tree*, int> isomorphismClasses2 = GeneralFunctionsForGraphs::generateAllSpanningTrees(edges2, n2, "kostryG2.txt");
    std::cout << "unlabeled spanning trees present in both graphs:" << std::endl;

    unsigned long long numberOfSpanningTreesInCommom = 0;
    for (auto it1 = isomorphismClasses1.begin(); it1 != isomorphismClasses1.end(); it1++) {
        for (auto it2 = isomorphismClasses2.begin(); it2 != isomorphismClasses2.end(); it2++) {
            if (it1->first->checkIsomorphism(it2->first)) {
                //std::cout << "izom\n";
                numberOfSpanningTreesInCommom++;
                GeneralFunctionsForGraphs::printGraph(it1->first->getEdgesOfTree());
            }
        }
    }

    for (auto it = isomorphismClasses1.begin(); it != isomorphismClasses1.end(); it++) {
        delete it->first;
    }
    for (auto it = isomorphismClasses2.begin(); it != isomorphismClasses2.end(); it++) {
        delete it->first;
    }
    std::cout << std::endl << numberOfSpanningTreesInCommom << " total" << std::endl;
}

