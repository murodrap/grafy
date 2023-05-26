#include <stdio.h>
#include <vector>
#include <map>
#include <climits>
#include <string>
#include <sstream>
#include <cmath>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex> 

#include "collectingRegularGraphs.h"

using Graphs = std::vector<std::string>;

/**
 * checks whether the given graph doesn't have equal or lower nuber of spanning trees that the currently min value
 * updates the values if necessary
 *
 * @param number number of spanning trees of graphs from graphs parameter
 * @param graphs vector of graphs with the same number of spanning trees
 */
void ColRegular::updateMin(long long number, const Graphs& graphs) {
    if (number == minK) {
        minG.insert(minG.end(), graphs.begin(), graphs.end());
    }

    if (number < minK) {
        minK = number;
        minG.clear();
        minG.insert(minG.end(), graphs.begin(), graphs.end());
    }
}

/**
 * checks whether the given graph doesn't have equal or higher nuber of spanning trees that the currently max value
 * updates the values if necessary
 *
 * @param number number of spanning trees of graphs from graphs parameter
 * @param graphs vector of graphs with the same number of spanning trees
 */
void ColRegular::updateMax(long long number, const Graphs& graphs) {
    if (number == maxK) {
        if (maxG.size() < maxStroredGraphs) {
            maxG.insert(maxG.end(), graphs.begin(), graphs.end());
        }
    }

    if (number > maxK) {
        maxK = number;
        maxG.clear();
        maxG.insert(maxG.end(), graphs.begin(), graphs.end());
    }

}

/**
 * writes max/min part of final results to file
 *
 * @param type specifies whether the followind data are for graphs with minimum or maximum number of spanning trees
 * @param number number of spanning trees for the specified part of results
 * @param graphs graphs with the corresponding number of spanning trees
 * @param file file stream to write to
 */
void ColRegular::graphsToFile(std::string type, long long number, const Graphs& graphs, std::ofstream& file) {
    file << type << " " << graphs.size() << " " << number << "\n";
        
    for (const std::string& graph: graphs) {
        file << graph << std::endl;
    }

}

/**
 * writes the final results to output file
 */
void ColRegular::writeToFile() {

    std::stringstream nameOfFile;
    nameOfFile << "maxMinReg" << reg << "-" << n << "-" << numberOfFiles << ".txt";
    std::ofstream file2;
    file2.open (nameOfFile.str());
    if (file2.is_open()) {
        graphsToFile("min", minK, minG, file2);
        graphsToFile("max", maxK, maxG, file2);
        file2.close();
    }
    else {
        std::cout << "Failed to open file " << nameOfFile.str() << " and to write the results" << std::endl;
    }
    
}

/**
 * reads max/min part of partial results from file
 *
 * @param file file to read from
 * @return pair where fist value is number of spanning trees, the second is vector of graphs read from the file 
 */
std::pair<long long, const Graphs> ColRegular::readResults(std::ifstream& file) {
    std::string line;
    std::string max_min;
    std::getline(file, line);
    std::istringstream iss(line);
    long long numberOfSpanningTrees;
    int numberOfGraphs;
    iss >> max_min;
    if (max_min == "0") {
        return std::make_pair(0, Graphs());
    }
    iss >> numberOfGraphs;
    iss >> numberOfSpanningTrees;
    Graphs graphs = Graphs();
    graphs.reserve(numberOfGraphs);
    
    for (int i = 0; i < numberOfGraphs; i++) {
        std::string graph;
        std::getline(file, graph);
        graphs.emplace_back(graph);
    }
    
    return std::make_pair(numberOfSpanningTrees, std::move(graphs));
}

/**
 * reads partial results from a file of name prefix-fileNumber and updates the final results accordingly
 *
 * @param fileNumber index of fle to read from
 */
void ColRegular::getResultsFromFile(int fileNumber) {
    std::ifstream file;

    std::stringstream nameOfFile;
    nameOfFile << fileFrom << "-" << fileNumber;
    file.open(nameOfFile.str());
    if (!file.is_open()) {
        std::cout << "Failed to open file " << nameOfFile.str() << std::endl;
        return;
    }

    std::pair<long long, const Graphs> results = readResults(file);
    long long numberOfSpanningTrees = results.first;
    if (numberOfSpanningTrees == 0) {
        file.close();
        return;
    }
    const Graphs& graphs = results.second;

    updateMin(numberOfSpanningTrees, graphs);

    std::pair<long long, const Graphs> results2 = readResults(file);
    long long numberOfSpanningTrees2 = results2.first;
    const Graphs& graphs2 = results2.second;

    updateMax(numberOfSpanningTrees2, graphs2);
   
    file.close();
}

/**
 * reads partial results from numberOfFIles files and filters out the final results which are ten written to a file
 */
void ColRegular::collectResults() {
    for (int i = 1; i <= numberOfFiles; i++) {
        getResultsFromFile(i);
    }    
    writeToFile();
}