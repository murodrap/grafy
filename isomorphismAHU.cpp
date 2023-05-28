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


/**
 * for given root, computes code of the tree using AHU algorithm
 *
 * @param root vertex used for rooting non-oriented tree
 * @return characteristic code of tree rooted in given vertex
 */
std::string Tree::codeOfTreeAHU(int root) {
    visitedVertices.clear();
    visitedVertices.insert(root);
    return codeOfVertexAHU(root);

}

/**
 * finds one of the possible most distant vertices from initial vertex
 *
 * @param v initial vertex
 * @return pair where first element is most distant vertex from v, the other is list of vertices on the path to this vertex
 */
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

/**
 * finds all possible central vertices of a tree
 *
 * @return vector with all possible roots of the tree
 */
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

/**
 * computes code of a subtree with specified root
 * 
 * @param vertex root of the current subtree
 * @return code of subtree rooted in given vertex
 */
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

/**
 * decides, using AHU algorithm, whether a given tree is ispomorphic with the current tree
 *
 * @param tree2 pointer to the other tree
 * @return true if the threes are isomorphic, false othervise
 */
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