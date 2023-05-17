#include <stdio.h>
#include <vector>
#include <set>
#include <map>
#include <climits>
#include <string>
#include <sstream>
#include <cmath>
#include <iostream>
#include <fstream>
#include <chrono>

#include "spanningTreeCounting.h"
#include "processingBiergularGraphs.h"

using Edges = std::vector<std::vector<int>>;
using Lines = std::vector<std::string>;


void ProcBiregular::edgeCombinations(int remaining, int indexFrom, const Edges& edges, Edges& currentEdges, std::vector<int>& usedVertices, std::set<std::vector<int>>& edgesResult) {
    
    if (!remaining) {
        Edges currentGraphEdges = Edges((n*reg + reg2) / 2);
        copy(edgesResult.begin(), edgesResult.end(), currentGraphEdges.begin());
        long long numberOfSpannigTrees = counter.countForGraph(currentGraphEdges);
        updateValues(numberOfSpannigTrees, currentGraphEdges);
        return;
    }
    if (remaining > edges.size() - indexFrom) {
        return;
    }
    for (int i = indexFrom; i <= edges.size() - remaining; i++) {
        int v = edges[i][0];
        int u = edges[i][1];
       
        if (multipleEdgeCheck(u, v, usedVertices)) {
                continue;
        }
        
        usedVertices[u] = 1;
        usedVertices[v] = 1;
        currentEdges.push_back(edges[i]);
        edgesResult.erase(edges[i]);
        std::vector<int> h1 = {u, n};
        std::vector<int> h2 = {v, n};
        edgesResult.insert(h1);
        edgesResult.insert(h2);
        edgeCombinations(remaining - 1, i+1, edges, currentEdges, usedVertices, edgesResult);
        currentEdges.pop_back();
        edgesResult.insert(edges[i]);
        edgesResult.erase(h1);
        edgesResult.erase(h2);
        usedVertices[u] = 0;
        usedVertices[v] = 0;
    }
    return;
}

bool ProcBiregular::multipleEdgeCheck(int u, int v, std::vector<int>& usedVertices){
    if (usedVertices[u]) {
            return true;
        }
    return usedVertices[v];
}

void ProcBiregular::processGraph(const Lines& graph) {
    Edges edges = getEdges(graph);
    Edges usedEdges; 
    std::vector<int> usedVert = std::vector<int>(n);
    std::set<std::vector<int>> currentGraph;
    for (auto edge : edges) {
        currentGraph.insert(edge);
    }
    edgeCombinations(reg2/2, 0, edges, usedEdges, usedVert, currentGraph);
    
}

