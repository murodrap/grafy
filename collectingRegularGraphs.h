#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>
#include <iostream>


class ColRegular {
    
    
    

    unsigned int maxStroredGraphs = 1000;

    using Graphs = std::vector<std::string>;
    
    void updateMin(long long number, const Graphs& graphs);
    void updateMax(long long number, const Graphs& graphs);
    
    
    virtual void writeToFile();
    std::pair<long long, const Graphs> readResults(std::ifstream& file);
    virtual void getResultsFromFile(int fileNumber);

protected:
    std::string fileFrom;
    int numberOfFiles;
    int n;
    int reg;

    Graphs maxG;
    Graphs minG;
    long long maxK = 1;
    long long minK = LLONG_MAX;

    void graphsToFile(std::string type, long long number, const Graphs& graphs, std::ofstream& file);

public:


    ColRegular(std::string file, int number, int n2, int reg2)
    : fileFrom(file)
    , numberOfFiles(number)
    , n(n2)
    , reg(reg2)
    {
        std::cout << "collecting results from " << number << " files" << std::endl;

    };
    void collectResults();

    
    
    
};