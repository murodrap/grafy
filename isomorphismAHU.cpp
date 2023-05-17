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
    std::vector<std::pair<int, std::vector<int>>> nextVertices = {std::make_pair(v, c)};
    std::vector<std::pair<int, std::vector<int>>> previousVertices;
    
    visitedVertices.clear();
    visitedVertices.insert(v);
    
    while (!nextVertices.empty()) {
        std::vector<std::pair<int, std::vector<int>>> newPairs;
        for (auto vertexPath : nextVertices) {
            
            int u = vertexPath.first;

            std::vector<int>& path = vertexPath.second;
            
            for (int neighbour : graph.find(u)->second) {
                if (visitedVertices.find(neighbour) == visitedVertices.end()) {
                    visitedVertices.insert(neighbour);

                    std::vector<int> pathExtended = path;
                    pathExtended.push_back(neighbour);
                    newPairs.push_back({neighbour,pathExtended});
                }
            }
        }
        
        previousVertices = std::move(nextVertices);
        nextVertices = std::move(newPairs);
    }
    return previousVertices[0];
}

std::vector<int> Tree::rootsSearch() {

    int x = 0;
    std::pair<int, std::vector<int>> vertex1Path1 = mostDistantVertex(x);
    std::pair<int, std::vector<int>> vertex2Path2 = mostDistantVertex(vertex1Path1.first);
    const std::vector<int>& path2 = vertex2Path2.second;
    std::vector<int> getRoots = {path2[path2.size()/2]};
    
    if (!(path2.size() % 2)) {
        getRoots.push_back(path2[path2.size()/2 - 1]);
    }
    return getRoots;

}

std::string Tree::codeOfVertexAHU(int vertex) {

    std::vector<std::string> codeOfSubtree;
    for (int neighbour: graph.find(vertex)->second) {
        if (visitedVertices.find(neighbour) == visitedVertices.end()) {
            visitedVertices.insert(neighbour);
            codeOfSubtree.emplace_back(codeOfVertexAHU(neighbour));
        }
    }
    std::sort(codeOfSubtree.begin(), codeOfSubtree.end(), std::greater<std::string>());
    std::stringstream code;
    code << "0";
    for (const std::string& childVertexCode : codeOfSubtree) {
        code << childVertexCode;
    }

    code << "1";

    return code.str();

}


bool Tree::checkIsomorphism(Tree* tree2) {
    if (tree2->getNumberOfVertices() != getNumberOfVertices()) {
        return false;
    }

    if (getRoots().size() != tree2->getRoots().size()) {
        return false;
    }
    for (auto code1 : getAHUcodes()) {
        for (auto code2 : tree2->getAHUcodes()) {
            if (code1 == code2) {
                return true;
            }
        }
    }

    return false;
}