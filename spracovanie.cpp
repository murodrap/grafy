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

using Hrany = std::vector<std::vector<int>>;

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
        //std::cout << riadok << "--" << vrch << "--\n";
        //std::cout << vrch << " ttt " << susedia;
        
        int v = stoi(vrch);
        //std::cout << v << "\n";
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


    //long this.spracovanych = 0;
    
    
    bool zacatyGraf = false;
    //auto start = high_resolution_clock::now();
    //auto stop = high_resolution_clock::now();

    oneapi::tbb::parallel_pipeline( /*max_number_of_live_token=*/4,
        oneapi::tbb::make_filter<void,Riadky*>(
            oneapi::tbb::filter_mode::serial_in_order,
            [&](oneapi::tbb::flow_control& fc)-> Riadky* {
                //stop = high_resolution_clock::now();
                //auto duration = duration_cast<microseconds>(stop - start);
                //std::cout << "generovanie: " << duration_cast<microseconds>(stop - start).count() << std::endl;
                Riadky* vrcholy = new Riadky(n);
                int index = 0;
                std::string riadok;
                
                while (std::getline(std::cin, riadok)) {
                    if (riadok[0] == 'G') {
                        zacatyGraf = true;
                    }
                    else if (!zacatyGraf || riadok.size() == 0) {
                        continue;
                    }
                    
                    else if (zacatyGraf){
                        vrcholy->at(index) = riadok;
                        index++;
                        if (index == n) {
                            //spracovanie grafu
                            
                            index = 0;
                            
                            zacatyGraf = false;
                            
                            ///////////////jedenGraf(vrcholy);
                            //start = high_resolution_clock::now();
                            return vrcholy;
                        }
                    }
                 }
                fc.stop();
                return nullptr;
            }
        ) &
        oneapi::tbb::make_filter<Riadky*,std::pair<long, Hrany*>>(
            oneapi::tbb::filter_mode::parallel,
            [this](Riadky* riadky){
                auto vysledok = jedenGraf(*riadky);
                delete riadky;
                return vysledok;
            }    
        ) &
        oneapi::tbb::make_filter<std::pair<long, Hrany*>,void>(
            oneapi::tbb::filter_mode::serial_in_order,
            [this](std::pair<long, Hrany*> pocetGraf) {
                kontrolaHodnot(pocetGraf.first, *pocetGraf.second);
                spracovanych++;
                //if((spracovanych % 10000) == 0) {
                //    std::cout << spracovanych << "\n";
                //}
                delete pocetGraf.second;
            }
        )
    );

    

    

    zapisDoSUboru();

}