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

#include "rozdelovanieVysledkov.h"


using Graf = std::vector<std::string>;
using Grafy = std::vector<Graf>;


void RozdelujVysledky::grafyDoSuboru(const Grafy& grafy) {
    mtxPosielanie.lock();
    std::ofstream& subor = suboryVon[komuPoslat];
    komuPoslat = (komuPoslat+1) % pocetSuborov;

    
    
    for (const Graf& graf : grafy) {
        if (graf.empty()) {
            break;
        }
        subor << "Graph" << std::endl;
        for (const std::string& riadok : graf) {
            subor << riadok << std::endl;
        }
        
    }
    mtxPosielanie.unlock();
}


void RozdelujVysledky::zbieranieGrafovSuboru(int cast) {
    std::ifstream subor1;

    std::string meno1(suborZ+"-"+std::to_string(cast));

    subor1.open(meno1);
    if (!subor1.is_open()) {
        std::cout << "nepodarilo sa otvorit subor " << meno1 << std::endl;
        return;
    }


    Grafy grafy(velkostSkupiny);
    Graf graf(n);
    int nacitanych = 0;
    int index = 0;
    std::string riadok;
    bool zacatyGraf = false;
   
    while (std::getline(subor1, riadok)) {
        if (riadok.empty()) {
            continue;
        }
        if (riadok[0] == 'G') {
            zacatyGraf = true;
        }
        else if (!zacatyGraf || riadok.empty()) {
            continue;
        }
        else if (zacatyGraf) {
            graf[index] = std::move(riadok);
            index++;
            
        
            if (index == n) {
                zacatyGraf = false;
                index = 0;
                grafy[nacitanych]= std::move(graf);
                graf = Graf(n);
                nacitanych++;
                
                if (nacitanych == velkostSkupiny) {
                    nacitanych = 0;
                    grafyDoSuboru(grafy);
                }
            }
        }
    }
    grafyDoSuboru(grafy);
    subor1.close();
}

void RozdelujVysledky::rozdelovanieVysledkov() {
    for (int i = 1; i <= pocetSuborov; i++) {
        std::string meno(suborDo+"-"+std::to_string(i));
        std::ofstream s;
        suboryVon.emplace_back(std::ofstream(meno));


    }

    std::vector<std::thread> citace;
    
    for (int i = 1; i <= pocetSuborov; i++) {
        citace.emplace_back(std::thread(&RozdelujVysledky::zbieranieGrafovSuboru, this, i));
    }

    for (int i = 0; i < pocetSuborov; i++) {
        if (citace[i].joinable()) {
            citace[i].join();
        }
    }
    for (int i = 0; i < pocetSuborov; i++) {
        suboryVon[i].close();
    }

}



