#pragma once
#include <stdio.h>
#include <vector>
#include <set>
#include <climits>
#include <string>

#include "processingRegularGraphs.h"
#include "generalGraphs.h"


class ProcBiregular : public ProcRegular{
    int reg2;
    
    using Edges = std::vector<std::vector<int>>;
    using Lines = std::vector<std::string>;

    bool multipleEdgeCheck(int u, int v, std::vector<int>& usedVertices);
    void edgeCombinations(int remaining, int indexFrom, const Edges& edges, Edges& currentEdges, std::vector<int>& usedVertices, std::set<std::vector<int>>& edgesResult);
    void processGraph(const Lines& graph) override;


public:
    ProcBiregular(std::string file, int reg12, int n2, int reg22)
    : ProcRegular(file, 0, n2+1)
    , reg2(reg22)
    {
        reg = reg12;
        n -= 1;
        std::cout << reg << "-regular graphs on " << n << " vertices, additional vertex of degree " << reg2 << std::endl;
        if (!GeneralFunctionsForGraphs::checkGraphExistence(n, reg, 1, reg2)) {
            counter.koniec();
            exit(1);
        }
    };
    
};