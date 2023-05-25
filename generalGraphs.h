#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include <map>

#include "spanningTreeCounting.h"
#include "unlabeledSpanningTrees.h"
#include "isomorphismAHU.h"

using Edges = std::vector<std::vector<int>>;
using AdjList = std::map<int, std::vector<int>>;

class GeneralFunctionsForGraphs
{
    static bool havelHakimi(int n1, int k1, int n2, int k2);
    static Edges stringToEdges(std::string& listOfEdges);
    static AdjList stringToAdjList(std::string& listOfEdges, int n);
    static bool isomorphicGraphs(const AdjList& g1, int n1, const AdjList& g2, int n2);
    static void printGraph(const Edges& graph);
    
    public:
        
        static bool checkGraphExistence(int n1, int k1, int n2, int k2);
        static long long countSpanningTrees(const Edges& edges, int reg, int n) {
            SpanningTreeCounter counter = SpanningTreeCounter(n, reg);
            long long kostier = counter.countForGraph(edges);
            return kostier;
            
        }
        static long long countSpanningTrees(std::string& edges, int reg, int n) {
            return countSpanningTrees(stringToEdges(edges), reg, n);
        }
        static bool isomorphicGraphs(std::string& g1, int n1, std::string& g2, int n2);

        static Edges spanningTreeBFS(std::string& edges, int n) {
            return spanningTreeBFS(stringToAdjList(edges, n), n);
        }
        static Edges spanningTreeBFS(const AdjList& graph, int n);

        static const std::map<Tree*, int> generateAllSpanningTrees(const Edges& edges, int n, const std::string& fileTo) {
            Onete o = Onete(n, edges.size());

            const std::map<Tree*, int> triedy = o.generateAllSpanningTrees(edges);
            o.writeIsomorphismClassesToFile(fileTo);
            return triedy;
        }
        static const std::map<Tree*, int> generateAllSpanningTrees(std::string& edges, int n, const std::string& fileTo) {
            return generateAllSpanningTrees(stringToEdges(edges), n, fileTo);
        }
        static void compareUnlabeledSpanningTrees(std::string& g1, int n1, std::string& g2, int n2);

        
};