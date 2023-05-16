#pragma once
#include <stdio.h>
#include <vector>
#include <set>
#include <climits>
#include <string>

#include "processingRegularGraphs.h"
#include "unlabeledSpanningTrees.h"


class SpracujCeleTriedy : public ProcRegular{
    int reg2;
    Onete o;
    std::vector<std::pair<unsigned long long, unsigned long long>> kostryTriedyPocty;
    
    using Edges = std::vector<std::vector<int>>;
    using Lines = std::vector<std::string>;

    void processGraph(const Lines& graph) override;
    void writeToFile() override;


public:
    SpracujCeleTriedy(std::string file, int reg2, int n2)
    : ProcRegular(file, reg2, n2)
    , o(n2, n2 * reg2 / 2)
    {
        
    };
    
};