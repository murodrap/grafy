#include <stdio.h>
#include <iostream>
#include <string>

#include "generalGraphs.h"

void spanningTreeCounting() {
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

void isomorphism() {
  std::string graph1;
  std::string graph2;
  std::cout << "number of vertices: "; 
  std::getline(std::cin, graph1);
  int n1 = std::stoi(graph1);
  std::cout << "edge list of first graph: ";
  std::getline(std::cin, graph1);

  std::cout << "edge list of second graph: ";
  std::getline(std::cin, graph2);
  if (GeneralFunctionsForGraphs::isomorphicGraphs(graph1, n1, graph2, n1)) {
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
  const std::map<Tree*, int> isomorphismClassses = GeneralFunctionsForGraphs::generateAllSpanningTrees(graph, n, file);
  for (auto it = isomorphismClassses.begin(); it != isomorphismClassses.end(); it++) {
    delete it->first;
  }
}

void compareSpanningTrees() {
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

void menu() {
  std::cout << "===============================" << std::endl;
  std::cout << "spanning tree counting: 1" << std::endl;
  std::cout << "tree isomporphism: 2" << std::endl;
  std::cout << "spanning tree enumeration: 3" << std::endl;
  std::cout << "spanning tree intersection: 4" << std::endl;
  std::cout << "exit: 5" << std::endl;
  std::cout << "===============================" << std::endl;
  
  std::string userInput;
  std::getline(std::cin, userInput);

  try{
    if (userInput == "1") {
      spanningTreeCounting();
    }
    else if (userInput == "2") {
      isomorphism();
    }
    else if (userInput == "3") {
      generateAllSpanningTrees();
    }
    else if (userInput == "4") {
      compareSpanningTrees();
    }
    else if (userInput == "5") {
      exit(0);
    }
    else {
      std::cout << "invalid option" << std::endl;
    }
  }
  catch (...){
    std::cout << "input was in unsupported format, computations couldn't be completed" << std::endl;
    menu();
  }
  std::cout << std::endl;
  menu();
}

int main(int argc, char *argv[])
{
    menu();

    return 0;
}
