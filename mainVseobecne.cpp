#include <stdio.h>
#include <iostream>
#include <string>

#include "vseobecne.h"

void pocitanieKostier() {
  std::string graf;
  std::cout << "zadajte pocet vrcholov: "; 
  std::getline(std::cin, graf);
  int n = std::stoi(graf);

  std::cout << "zadajte edge list grafu: ";
  std::getline(std::cin, graf);
  if (graf.empty()) {
    std::cout << "prazdny graf" << std::endl;
  }
  std::cout << "pocet kostier v zadanom grafe je " << VseobecneFunkcie::pocetKostier(graf, 0, n) << std::endl;
}

void izomorfizmus() {
  std::string graf1;
  std::string graf2;
  std::cout << "zadajte pocet vrcholov prveho grafu: "; 
  std::getline(std::cin, graf1);
  int n1 = std::stoi(graf1);
  std::cout << "zadajte edge list prveho grafu: ";
  std::getline(std::cin, graf1);

  std::cout << "zadajte pocet vrcholov druheho grafu: "; 
  std::getline(std::cin, graf2);
  int n2 = std::stoi(graf2);
  std::cout << "zadajte edge list druheho grafu: ";
  std::getline(std::cin, graf2);
  if (VseobecneFunkcie::izomorfneGrafy(graf1, n1, graf2, n2)) {
    std::cout << "grafy su izomorfne" << std::endl;
  }
  else {
    std::cout << "grafy nie su izomorfne" << std::endl;
  }
}

void generovanieKostier() {
  std::string graf;
  std::cout << "zadajte pocet vrcholov grafu: ";
  std::getline(std::cin, graf);
  int n = std::stoi(graf);
  std::cout << "zadajte edge list grafu: ";
  std::getline(std::cin, graf);
  std::string subor;
  std::cout << "zadajte nazov vystupneho suboru: ";
  std::getline(std::cin, subor);
  VseobecneFunkcie::generovanieKostier(graf, n, subor);
}

void porovnanieKostier() {
  std::string graf1;
  std::string graf2;
  std::cout << "zadajte pocet vrcholov prveho grafu: "; 
  std::getline(std::cin, graf1);
  int n1 = std::stoi(graf1);
  std::cout << "zadajte edge list prveho grafu: ";
  std::getline(std::cin, graf1);

  std::cout << "zadajte pocet vrcholov druheho grafu: "; 
  std::getline(std::cin, graf2);
  int n2 = std::stoi(graf2);
  std::cout << "zadajte edge list druheho grafu: ";
  std::getline(std::cin, graf2);

  VseobecneFunkcie::porovnamieKostier(graf1, n1, graf2, n2);
}

void ponuka() {
  std::cout << "**********************" << std::endl;
  std::cout << "pocet kostier grafu: 1" << std::endl;
  std::cout << "izomorfizmus grafov: 2" << std::endl;
  std::cout << "vsetky kostry grafu: 3" << std::endl;
  std::cout << "porovnanie kostier grafov: 4" << std::endl;
  std::cout << "koniec: 5" << std::endl;
  std::cout << "**********************" << std::endl;
  
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
