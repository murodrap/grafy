#include <stdio.h>
#include <vector>
#include <map>
#include <climits>
#include <string>
#include <sstream>
#include <cmath>
#include <iostream>
#include <fstream>
#include <chrono>

#include "spanningTreeCounting.h"
#include "processingRegularGraphs.h"

using Edges = std::vector<std::vector<int>>;

void ProcRegular::updateValues(long long number, const Edges& edges) {

    if (number == maxK) {
        if (maxG.size() < maxStroredGraphs) {
            maxG.push_back(edges);
        }
    }

    if (number > maxK) {
        maxK = number;
        maxG.clear();
        maxG.push_back(edges);
    }
    if (number == minK) {
        if (minG.size() < maxStroredGraphs) {
            minG.push_back(edges);
        }
    }

    if (number < minK) {
        minK = number;
        minG.clear();
        minG.push_back(edges);
    }

}

long ProcRegular::podlaVzorca() {
    std::map<int, int> hodn{{4, 16}, {6, 75}, {8, 256}, {12, 2112}};


    auto h = hodn.find(this->n);
    if (h != hodn.end()) {
        return h->second;
    }
   
    if (n%4 == 0) {
        long stvorkove = trunc(pow(8, trunc((n-3*5)/4)));
        return trunc(pow(24, 3)) * stvorkove;
    }
    long stvorkove = trunc(pow(8, trunc((n-2*5)/4)));
    return trunc(pow(24, 2)) * stvorkove;
}

Edges ProcRegular::getEdges(const Lines& lines) {
    Edges edges(n*reg/2);
    int index = 0;
    for (const std::string& riadok : lines) {
        std::stringstream ss(riadok);
        std::string vertex;
        std::string susedia;
        
        getline(ss, vertex, ':');
        vertex.pop_back();
        getline(ss, susedia, ':');
        susedia.erase(0, 1);
        
        int v = stoi(vertex);
        std::string sused;  
        std::stringstream ss2(susedia);
        while (!ss2.eof()) {
            getline(ss2, sused, ' ');
            if (!sused.size()) {
                continue;
            }
            int u = stoi(sused);
            if (u > v) {
                std::vector<int> edge(2);
                edge[0] = v - 1;
                edge[1] = u - 1;
                edges[index] = edge;
                index++;
            }
        }
    }
    return edges;
}

void ProcRegular::graphsToFile(long long number, const std::vector<Edges>& graphs, std::ofstream& sub) {
    sub <<  graphs.size() << " " << number << "\n";
    
    for (const Edges& graph : graphs) {
        sub << "[";
        bool prve = true;
        for (const std::vector<int>& edge : graph) {
            if (prve) {
                prve = false;
            }
            else {
                sub << ", ";
            }
            sub << "(" << edge[0] << ", " << edge[1] << ")";
        }

        sub << "]\n";
    }


}

void ProcRegular::writeToFile(){
    fileTo << "min ";
    graphsToFile(minK, minG, fileTo);
    fileTo << "max ";
    graphsToFile(maxK, maxG, fileTo);

}

void ProcRegular::processGraph(const Lines& graph) {
    Edges edges = getEdges(graph);
    long kostier = counter.countForGraph(edges);
    updateValues(kostier, edges);
}

void ProcRegular::processAll() {
    Lines vrcholy(n);
    int index = 0;
    std::string riadok;
    bool zacatyGraf = false;
   
    while (std::getline(std::cin, riadok)) {
        if (riadok[0] == 'G') {
            zacatyGraf = true;
        }
        else if (!zacatyGraf || riadok.empty()) {
            continue;
        }
        
        else if (zacatyGraf){
            vrcholy.at(index) = riadok;
            index++;
            
            if (index == n) {
                processGraph(vrcholy);
                index = 0;
                zacatyGraf = false;
            }
        }
    }

    writeToFile();
    fileTo.close();
    counter.koniec();

}