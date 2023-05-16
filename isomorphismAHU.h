#pragma once
#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <climits>
#include <string>

using Edges = std::vector<std::vector<int>>;
using AdjList = std::map<int, std::vector<int>>;

class Tree {
    AdjList graph;
    int n;
    Edges edges;

    std::vector<int> roots;
    std::vector<std::string> codes;
    std::set<int> visitedVertices;
    std::pair<int, std::vector<int>> mostDistantVertex(int v);
    std::string codeOfVertexAHU(int vertex);
    std::vector<int> rootsSearch();
    std::string codeOfTreeAHU(int root);


    public:
        
        bool checkIsomorphism(Tree* tree2);
        Tree(const AdjList& graph1, int n1)
        : graph(graph1)
        , n(n1) {
            for (int u = 0; u < n; u++) {
                for (int v : graph.find(u)->second) {
                    if (v > u) {
                        edges.push_back({u, v});

                    }
                }
            }
            roots = rootsSearch();
            for (int v : roots) {
                codes.emplace_back(codeOfTreeAHU(v));
            }
        }

        Tree(const Edges& edges1, int n1)
        : edges(edges1)
        , n(n1) {
            for (int i = 0; i < n; i++) {
                graph[i] = std::vector<int>();
            }
            for (auto edge : edges) {
                int u = edge[0];
                int v = edge[1];
                graph[u].push_back(v);
                graph[v].push_back(u);
            }
            roots = rootsSearch();
            for (int v : roots) {
                codes.emplace_back(codeOfTreeAHU(v));
            }
            
        }

        int getNumberOfVertices() {
            return n;
        }

        const Edges& getEdgesOfTree() {
            return edges;
        }

        const std::vector<int>& getRoots() {
            return roots;
        }

        const std::vector<std::string>& getAHUcodes() {
            return codes;
        }
        
};