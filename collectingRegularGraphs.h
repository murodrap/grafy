#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>
#include <iostream>


class ColRegular {
    
    
    

    int maxStroredGraphs = 1000;

    using Graphs = std::vector<std::string>;
    
    void updateMin(long long number, const Graphs& graphs);
    void updateMax(long long number, const Graphs& graphs);
    
    
    virtual void writeToFile();
    std::pair<long long, const Graphs> readResults(std::ifstream& file);
    virtual void getResultsFromFile(int fileNumber);

protected:
    int n;
    int reg;
    int numberOfFiles;
    std::string fileFrom;
    Graphs maxG;
    Graphs minG;
    long long maxK = 1;
    long long minK = LLONG_MAX;

    void graphsToFile(std::string type, unsigned long long number, const Graphs& graphs, std::ofstream& file);

public:


    ColRegular(std::string file, int number, int n2, int reg2)
    : fileFrom(file)
    , numberOfFiles(number)
    , n(n2)
    , reg(reg2)
    {
        std::cout << "zberanie vysledkov pre " << number << " suborov" << std::endl;

    };
    void collectResults();

    
    
    
};