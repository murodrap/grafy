#pragma once
#include <stdio.h>
#include <vector>
#include <map>
#include <set>
#include <climits>
#include <string>

using Hrany = std::vector<std::vector<int>>;
using AdjList = std::map<int, std::vector<int>>;

class Strom {
    AdjList graf;
    int n;
    std::set<int> prejdeneVrcholy;
    std::pair<int, std::vector<int>> najvzdialenejsi(int v);
    std::string kodVrcholAHU(int vrch);


    public:
        std::string kodStromAHU(int koren);
        bool suIzomorfne(Strom* strom2);
        Strom(const AdjList& graf1, int n1)
        : graf(graf1)
        , n(n1) {

        }
        int pocetVrcholov() {
            return n;
        }

        std::vector<int> korene();
    
};