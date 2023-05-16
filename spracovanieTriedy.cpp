#include <stdio.h>
#include <vector>
#include <set>
#include <map>
#include <climits>
#include <string>
#include <sstream>
#include <cmath>
#include <iostream>
#include <fstream>
#include <chrono>

#include "unlabeledSpanningTrees.h"
#include "isomorphismAHU.h"
#include "spracovanieTriedy.h"

using Edges = std::vector<std::vector<int>>;
using Lines = std::vector<std::string>;

void SpracujCeleTriedy::processGraph(const Lines& graph) {
    Edges edges = getEdges(graph);
    unsigned long long pocetTried = o.generateAllSpanningTrees(edges).size();
    unsigned long long countSpanningTrees = o.getNumberOfSpanningTrees();
    kostryTriedyPocty.emplace_back(std::make_pair(countSpanningTrees, pocetTried));
}

void SpracujCeleTriedy::writeToFile(){
    fileTo << kostryTriedyPocty.size() << " grafov" << std::endl << std::endl;

    for (auto it = kostryTriedyPocty.begin(); it != kostryTriedyPocty.end(); it++) {
        fileTo  << "kostier: " << it->first << ", tried: " << it->second << std::endl;
    }
    o.deleteTrees();
}