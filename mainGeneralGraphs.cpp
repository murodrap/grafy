#include <stdio.h>
#include <iostream>
#include <string>

#include "generalGraphs.h"

void pocitanieKostier() {
  std::string graph;
  std::cout << "number of vertices: "; 
  std::getline(std::cin, graph);
  int n = std::stoi(graph);

  std::cout << "edge list of the graph: ";
  std::getline(std::cin, graph);
  if (graph.empty()) {
    std::cout << "graph has no edges" << std::endl;
  }
  std::cout << "number of spanning trees in the graph is: " << GeneralFunctionsForGraphs::countSpanningTrees(graph, 0, n) << std::endl;
}

void izomorfizmus() {
  std::string graph1;
  std::string graf2;
  std::cout << "number of vertices: "; 
  std::getline(std::cin, graph1);
  int n1 = std::stoi(graph1);
  std::cout << "edge list of first graph: ";
  std::getline(std::cin, graph1);

  std::cout << "edge list of second graph: ";
  std::getline(std::cin, graf2);
  if (GeneralFunctionsForGraphs::isomorphicGraphs(graph1, n1, graf2, n1)) {
    std::cout << "isomorphic" << std::endl;
  }
  else {
    std::cout << "non-isomorphic" << std::endl;
  }
}

void generateAllSpanningTrees() {
  std::string graph;
  std::cout << "number of vertices: ";
  std::getline(std::cin, graph);
  int n = std::stoi(graph);
  std::cout << "edge list of the graph: ";
  std::getline(std::cin, graph);
  std::string file;
  std::cout << "name of output file: ";
  std::getline(std::cin, file);
  const std::map<Tree*, int> triedy = GeneralFunctionsForGraphs::generateAllSpanningTrees(graph, n, file);
  for (auto it = triedy.begin(); it != triedy.end(); it++) {
    delete it->first;
  }
}

void porovnanieKostier() {
  std::string graph1;
  std::string graf2;
  std::cout << "number of vertices: "; 
  std::getline(std::cin, graph1);
  int n1 = std::stoi(graph1);
  std::cout << "edge list of first graph: ";
  std::getline(std::cin, graph1);

  std::cout << "edge list of second graph: ";
  std::getline(std::cin, graf2);

  GeneralFunctionsForGraphs::compareUnlabeledSpanningTrees(graph1, n1, graf2, n1);
}

void ponuka() {
  std::cout << "===============================" << std::endl;
  std::cout << "spanning tree counting: 1" << std::endl;
  std::cout << "tree isomporphism: 2" << std::endl;
  std::cout << "spanning tree enumeration: 3" << std::endl;
  std::cout << "spanning tree intersection: 4" << std::endl;
  std::cout << "exit: 5" << std::endl;
  std::cout << "===============================" << std::endl;
  
  std::string vyber;
  std::getline(std::cin, vyber);

  try{
    if (vyber == "1") {
      pocitanieKostier();
    }
    else if (vyber == "2") {
      izomorfizmus();
    }
    else if (vyber == "3") {
      generateAllSpanningTrees();
    }
    else if (vyber == "4") {
      porovnanieKostier();
    }
    else if (vyber == "5") {
      exit(0);
    }
    else {
      std::cout << "nepovoleny vyber" << std::endl;
    }
  }
  catch (...){
    std::cout << "input was in unsupported format, computations couldn't be completed" << std::endl;
    ponuka();
  }
  std::cout << std::endl;
  ponuka();
}

int main(int argc, char *argv[])
{
    ponuka();

    return 0;
}
