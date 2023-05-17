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
    for (const std::string& line : lines) {
        std::stringstream ss(line);
        std::string vertex;
        std::string neighbours;
        
        getline(ss, vertex, ':');
        vertex.pop_back();
        getline(ss, neighbours, ':');
        neighbours.erase(0, 1);
        
        int v = stoi(vertex);
        std::string neighbour;  
        std::stringstream ss2(neighbours);
        while (!ss2.eof()) {
            getline(ss2, neighbour, ' ');
            if (!neighbour.size()) {
                continue;
            }
            int u = stoi(neighbour);
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
        bool firstEdge = true;
        for (const std::vector<int>& edge : graph) {
            if (firstEdge) {
                firstEdge = false;
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
    long long numberOfSpanningTrees = counter.countForGraph(edges);
    updateValues(numberOfSpanningTrees, edges);
}

void ProcRegular::processAll() {
    Lines adjacencyListLines(n);
    int index = 0;
    std::string line;
    bool graphStarted = false;
   
    while (std::getline(std::cin, line)) {
        if (line[0] == 'G') {
            graphStarted = true;
        }
        else if (!graphStarted || line.empty()) {
            continue;
        }
        
        else if (graphStarted){
            adjacencyListLines.at(index) = line;
            index++;
            
            if (index == n) {
                processGraph(adjacencyListLines);
                index = 0;
                graphStarted = false;
            }
        }
    }

    writeToFile();
    fileTo.close();
    counter.koniec();

}