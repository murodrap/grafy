#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <climits>
#include <string>
#include <sstream>

#include <bits/stdc++.h>

#include "izomorfizmus.h"


std::string Strom::kodStromAHU(int koren) {
    prejdeneVrcholy.clear();
    prejdeneVrcholy.insert(koren);
    return kodVrcholAHU(koren);

}

std::pair<int, std::vector<int>> Strom::najvzdialenejsi(int v) {
    std::vector<int> c = {v};
    std::vector<std::pair<int, std::vector<int>>> naPrejdenie = {std::make_pair(v, c)};
    std::vector<std::pair<int, std::vector<int>>> predchadzajuce;
    
    prejdeneVrcholy.clear();
    prejdeneVrcholy.insert(v);
    
    while (!naPrejdenie.empty()) {
        std::vector<std::pair<int, std::vector<int>>> nove;
        for (auto vrchCesta : naPrejdenie) {
            int u = vrchCesta.first;
            std::vector<int>& cesta = vrchCesta.second;
            
            for (int potomok : graf.find(u)->second) {
                if (prejdeneVrcholy.find(potomok) != prejdeneVrcholy.end()) {
                    prejdeneVrcholy.insert(potomok);

                    std::vector<int> cestaRozsirena = cesta;
                    cestaRozsirena.push_back(potomok);
                    nove.push_back({potomok,cestaRozsirena});
                }
            }
        }
        predchadzajuce = std::move(naPrejdenie);
        naPrejdenie = std::move(nove);
    }
    return predchadzajuce[0];
}

std::vector<int> Strom::korene() {

    int x = 0;
    std::pair<int, std::vector<int>> v1Cesta1 = najvzdialenejsi(x);
    std::pair<int, std::vector<int>> v2Cesta2 = najvzdialenejsi(v1Cesta1.first);
    const std::vector<int>& cesta2 = v2Cesta2.second;
    std::vector<int> korene = {cesta2[cesta2.size()/2]};
    
    if (!(cesta2.size() % 2)) {
        korene.push_back(cesta2[cesta2.size()/2 - 1]);
    }
    return korene;

}

std::string Strom::kodVrcholAHU(int vrch) {

    std::vector<std::string> stredKodu;
    for (int potomok : graf.find(vrch)->second) {
        if (prejdeneVrcholy.find(potomok) != prejdeneVrcholy.end()) {
            prejdeneVrcholy.insert(potomok);
            stredKodu.emplace_back(kodVrcholAHU(potomok));
        }
    }
    std::sort(stredKodu.begin(), stredKodu.end(), std::greater<std::string>());
    std::stringstream kod;
    kod << "0";
    for (const std::string& kodPotomka : stredKodu) {
        kod << kodPotomka;
    }

    kod << "1";

    return kod.str();

}


bool Strom::suIzomorfne(Strom* strom2) {
    if (strom2->pocetVrcholov() != pocetVrcholov()) {
        return false;
    }
    std::vector<int> kor1 = korene();
    std::vector<int> kor2 = strom2->korene();
    if (kor1.size() != kor2.size()) {
        return false;
    }
    for (int k1 : kor1) {
        for (int k2 : kor2) {
            if (kodStromAHU(k1) == strom2->kodStromAHU(k2)) {
                return true;
            }
        }
    }

    return false;
}