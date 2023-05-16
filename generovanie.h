#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <string>
#include <fstream>
#include "spanningTreeCounting.h"
#include "generalGraphs.h"

class Generator {
    int reg1;
    int n1;
    int reg2;
    int n2;

    std::ofstream fileTo;
    SpanningTreeCounter counter;

    
    using Edges = std::vector<std::vector<int>>;
    std::vector<Edges> maxG;
    std::vector<Edges> minG;

    unsigned long long maxK = 1;
    unsigned long long minK = ULLONG_MAX;
    void updateValues(unsigned long long number, const Edges& edges);

    void graphsToFile(std::string type, unsigned long long number, const std::vector<Edges>& graphs, std::ofstream& sub);
    void writeToFile();

    void vsetkyGrafy(std::vector<int>& ostavajuceStupne, Edges& vybrateHrany, std::vector<int>& spojeniaDo);


public:
    Generator(int reg12, int n12, int reg22, int n22)
    : reg1(reg12)
    , n1(n12)
    , reg2(reg22)
    , n2(n22)
    , counter(SpanningTreeCounter(n1 + n2, 0))
    {
        std::cout << reg1 << " a " << reg2 << "-regularne graphs na " << n1 << " a " << n2 << " vrcholoch" << std::endl;
        if (!GeneralFunctionsForGraphs::checkGraphExistence(n1, reg1, n2, reg2)) {
            exit(1);
        }
    }

    void generovanie();
    
};
