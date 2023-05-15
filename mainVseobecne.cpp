#include <stdio.h>
#include <iostream>
#include <string>

#include "vseobecne.h"

void pocitanieKostier() {
  std::string graf;
  std::cout << "number of vertices: "; 
  std::getline(std::cin, graf);
  int n = std::stoi(graf);

  std::cout << "edge list of the graph: ";
  std::getline(std::cin, graf);
  if (graf.empty()) {
    std::cout << "graph has no edges" << std::endl;
  }
  std::cout << "number of spanning trees in the graph is: " << VseobecneFunkcie::pocetKostier(graf, 0, n) << std::endl;
}

void izomorfizmus() {
  std::string graf1;
  std::string graf2;
  std::cout << "number of vertices: "; 
  std::getline(std::cin, graf1);
  int n1 = std::stoi(graf1);
  std::cout << "edge list of first graph: ";
  std::getline(std::cin, graf1);

  std::cout << "edge list of second graph: ";
  std::getline(std::cin, graf2);
  if (VseobecneFunkcie::izomorfneGrafy(graf1, n1, graf2, n1)) {
    std::cout << "i" << std::endl;
  }
  else {
    std::cout << "non-isomorphic" << std::endl;
  }
}

void generovanieKostier() {
  std::string graf;
  std::cout << "number of vertices: ";
  std::getline(std::cin, graf);
  int n = std::stoi(graf);
  std::cout << "edge list of the graph: ";
  std::getline(std::cin, graf);
  std::string subor;
  std::cout << "name of output file: ";
  std::getline(std::cin, subor);
  const std::map<Strom*, int> triedy = VseobecneFunkcie::generovanieKostier(graf, n, subor);
  for (auto it = triedy.begin(); it != triedy.end(); it++) {
    delete it->first;
  }
}

void porovnanieKostier() {
  std::string graf1;
  std::string graf2;
  std::cout << "number of vertices: "; 
  std::getline(std::cin, graf1);
  int n1 = std::stoi(graf1);
  std::cout << "edge list of first graph: ";
  std::getline(std::cin, graf1);

  std::cout << "edge list of second graph: ";
  std::getline(std::cin, graf2);

  VseobecneFunkcie::porovnamieKostier(graf1, n1, graf2, n1);
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

  if (vyber == "1") {
    pocitanieKostier();
  }
  else if (vyber == "2") {
    izomorfizmus();
  }
  else if (vyber == "3") {
    generovanieKostier();
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
  std::cout << std::endl;
  ponuka();
}

int main(int argc, char *argv[])
{
    ponuka();

    
    return 0;
}
