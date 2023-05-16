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


void ColRegular::graphsToFile(std::string type, unsigned long long number, const Graphs& graphs, std::ofstream& file) {
    file << type << " " << graphs.size() << " " << number << "\n";
        
    for (const std::string& graph: graphs) {
        file << graph << std::endl;
    }

}

void ColRegular::writeToFile() {

    std::stringstream kamUkladat;
    kamUkladat << "maxMinReg" << reg << "-" << n << "-" << numberOfFiles << ".txt";
    std::ofstream subor2;
    subor2.open (kamUkladat.str());
    if (subor2.is_open()) {
        graphsToFile("min", minK, minG, subor2);
        graphsToFile("max", maxK, maxG, subor2);
        subor2.close();
    }
    else {
        std::cout << "Nepodarilo sa vytvorit file a zapisat donho vysledky";
    }
    
}

std::pair<long long, const Graphs> ColRegular::readResults(std::ifstream& file) {
    std::string riadok;
    std::string kus;
    std::getline(file, riadok);
    std::istringstream iss(riadok);
    long long kostier;
    int pocetGrafov;
    iss >> kus;
    if (kus == "0") {
        return std::make_pair(0, Graphs());
    }
    iss >> pocetGrafov;
    iss >> kostier;
    Graphs graphs = Graphs();
    graphs.reserve(pocetGrafov);
    
    for (int i = 0; i < pocetGrafov; i++) {
        std::string graph;
        std::getline(file, graph);
        graphs.emplace_back(graph);
    }
    
    return std::make_pair(kostier, std::move(graphs));
}


void ColRegular::getResultsFromFile(int fileNumber) {
    std::ifstream file;

    std::stringstream meno;
    meno << fileFrom << "-" << fileNumber;
    file.open(meno.str());
    if (!file.is_open()) {
        std::cout << "nepodarilo sa otvorit file " << meno.str() << std::endl;
        return;
    }

    std::pair<long long, const Graphs> vyslG = readResults(file);
    long long kostier = vyslG.first;
    if (kostier == 0) {
        file.close();
        return;
    }
    const Graphs& graphs = vyslG.second;

    updateMin(kostier, graphs);

    std::pair<long long, const Graphs> vyslG2 = readResults(file);
    long long kostier2 = vyslG2.first;
    const Graphs& grafy2 = vyslG2.second;

    updateMax(kostier2, grafy2);
   
    file.close();
}

void ColRegular::collectResults() {
    for (int i = 1; i <= numberOfFiles; i++) {
        getResultsFromFile(i);
    }    
    writeToFile();
}