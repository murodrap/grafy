#include <stdio.h>
#include <vector>
#include <map>
#include <climits>
#include <string>
#include <sstream>
#include <cmath>
#include <iostream>
#include <fstream>
#include "VypocetKostier.h"
#include "spracovanie.h"
#include "oneapi/tbb/parallel_pipeline.h"


#include <chrono>
using namespace std::chrono;

using Riadky = std::vector<std::string>;
using SkupinaGrafov = std::vector<Riadky>;
using Hrany = std::vector<std::vector<int>>;
using ParPocetAHrany = std::pair<long, std::vector<Hrany>*>;

void SpracujCele::kontrolaHodnot(long pocet, const Hrany& hrany) {
    //std::cout << "kostier " << pocet << "\n"; 

    if (pocet == maxK) {
        maxG.push_back(hrany);
    }

    if (pocet > maxK) {
        maxK = pocet;
        maxG.clear();
        maxG.push_back(hrany);
    }
    if (pocet == minK) {
        minG.push_back(hrany);
    }

    if (pocet < minK) {
        minK = pocet;
        minG.clear();
        minG.push_back(hrany);
    }

}



long SpracujCele::podlaVzorca() {
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

Hrany* SpracujCele::spracujGraf(const Riadky& riadky) {
    Hrany* hrany = new Hrany(n*reg/2);
    int index = 0;
    for (const std::string& riadok : riadky) {
        std::stringstream ss(riadok);
        std::string vrch;
        std::string susedia;
        
        getline(ss, vrch, ':');
        vrch.pop_back();
        getline(ss, susedia, ':');
        susedia.erase(0, 1);

        int v = stoi(vrch);
        std::string sused;  
        std::stringstream ss2(susedia);
        while (!ss2.eof()) {
            getline(ss2, sused, ' ');
            if (!sused.size()) {
                continue;
            }
            //std::cout << "sus " << sused << "--\n";
            int u = stoi(sused);
            if (u > v) {
                hrany->at(index) = {v - 1, u - 1};
                index++;
            }
        }
    }
    return hrany;
}

void SpracujCele::grafyDoSuboru(std::string typ, long pocet, const std::vector<Hrany>& grafy, std::ofstream& subor) {
    subor << typ << " " << pocet << "\n";
        
    for (const Hrany& graf : grafy) {
        subor << "[";
        bool prve = true;
        for (const std::vector<int>& hrana : graf) {
            if (prve) {
                prve = false;
            }
            else {
                subor << ", ";
            }
            subor << "(" << hrana[0] << ", " << hrana[1] << ")";
        }

        subor << "]\n";
    }

}

void SpracujCele::zapisDoSUboru() {
    std::stringstream kamUkladat;
    kamUkladat << "maxMinReg" << reg << "-" << n << ".txt";
    std::ofstream subor;
    subor.open (kamUkladat.str());
    if (subor.is_open()) {
        grafyDoSuboru("min", minK, minG, subor);
        grafyDoSuboru("max", maxK, maxG, subor);

        subor.close();
    }
    else {
        std::cout << "Unepodarilo sa vytvorit subor a zapisat donho vysledky";
    }
}

std::pair<long, Hrany*> SpracujCele::jedenGraf(const Riadky& graf) {
    Hrany* hrany = spracujGraf(graf);
    long kostrier = VypocetKostier::celkovyVypocet(*hrany, reg, n);
    
    return std::make_pair(kostrier, hrany);
}

void SpracujCele::celySubor() {

    oneapi::tbb::parallel_pipeline( /*max_number_of_live_token=*/maxSucasneSpracovanych,
        oneapi::tbb::make_filter<void,std::pair<SkupinaGrafov*, int>>(
            oneapi::tbb::filter_mode::serial_out_of_order,
            [this](oneapi::tbb::flow_control& fc)-> std::pair<SkupinaGrafov*, int> {
                
                SkupinaGrafov* grafy = new SkupinaGrafov(pocetGrafov);
                Riadky vrcholy(n);
                int index = 0;
                std::string riadok;
                nacitanychGrafov = 0;
                
                while (std::getline(std::cin, riadok)) {
                    if (riadok[0] == 'G') {
                        zacatyGraf = true;
                    }
                    else if (!zacatyGraf || riadok.size() == 0) {
                        continue;
                    }
                    
                    else if (zacatyGraf){
                        vrcholy[index] = riadok;
                        index++;
                        if (index == n) {
                            
                            index = 0;
                            
                            zacatyGraf = false;
                            
                            grafy->at(nacitanychGrafov) = std::move(vrcholy);
                            vrcholy = Riadky(n);
                            nacitanychGrafov++;
                            if (nacitanychGrafov == pocetGrafov) {
                                return std::make_pair(grafy, pocetGrafov);
                            }
                        }
                    }
                 }
                if (koniec) {
                    fc.stop();
                    return std::pair<SkupinaGrafov*, int>();
                }
                koniec = true;
                return std::make_pair(grafy, nacitanychGrafov);
            }
        ) &
        oneapi::tbb::make_filter<std::pair<SkupinaGrafov*, int>,std::vector<std::pair<long, Hrany*>>*>(
            oneapi::tbb::filter_mode::parallel,
            [this](std::pair<SkupinaGrafov*, int> grafyPocet){
                auto grafy = grafyPocet.first;
                std::vector<std::pair<long, Hrany*>>* spracovaneGrafy = new std::vector<std::pair<long, Hrany*>>();
                spracovaneGrafy->reserve(grafyPocet.second);

                for (int i  = 0; i < grafyPocet.second; i++) {
                    
                    auto vysledok = jedenGraf(grafy->at(i));
                    spracovaneGrafy->push_back(vysledok);
                }
                delete grafy;
                return spracovaneGrafy;
            }    
        ) &
        oneapi::tbb::make_filter<std::vector<std::pair<long, Hrany*>>*,void>(
            oneapi::tbb::filter_mode::serial_out_of_order,
            [this](std::vector<std::pair<long, Hrany*>>* poctyGrafy) {
                for (int i  = 0; i < poctyGrafy->size(); i++) {
                    kontrolaHodnot(poctyGrafy->at(i).first, *poctyGrafy->at(i).second);
                    delete poctyGrafy->at(i).second;
                }
                delete poctyGrafy;


                spracovanych+= pocetGrafov;
                   std::cout << spracovanych << "\n";
            }
        )
    );

    

    

    zapisDoSUboru();

}