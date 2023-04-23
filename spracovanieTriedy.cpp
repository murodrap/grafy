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

#include "vsetkyKostry.h"
#include "izomorfizmus.h"
#include "spracovanieTriedy.h"

using Hrany = std::vector<std::vector<int>>;
using Riadky = std::vector<std::string>;

void SpracujCeleTriedy::jedenGraf(const Riadky& graf) {
    Hrany hrany = spracujGraf(graf);
    unsigned long long pocetTried = o.generovanieKostier(hrany).size();
    unsigned long long pocetKostier = o.kostry();
    kostryTriedyPocty.emplace_back(std::make_pair(pocetKostier, pocetTried));
}

void SpracujCeleTriedy::zapisDoSUboru(){
    suborDo << kostryTriedyPocty.size() << " grafov" << std::endl << std::endl;

    for (auto it = kostryTriedyPocty.begin(); it != kostryTriedyPocty.end(); it++) {
        suborDo  << "kostier: " << it->first << ", tried: " << it->second << std::endl;
    }
    o.vymazanieStromov();
}