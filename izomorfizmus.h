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
    Hrany hrany;

    std::vector<int> koreneStromu;
    std::vector<std::string> kody;
    std::set<int> prejdeneVrcholy;
    std::pair<int, std::vector<int>> najvzdialenejsi(int v);
    std::string kodVrcholAHU(int vrch);
    std::vector<int> koreneVypocet();
    std::string kodStromAHU(int koren);


    public:
        
        bool suIzomorfne(Strom* strom2);
        Strom(const AdjList& graf1, int n1)
        : graf(graf1)
        , n(n1) {
            for (int u = 0; u < n; u++) {
                for (int v : graf.find(u)->second) {
                    if (v > u) {
                        hrany.push_back({u, v});

                    }
                }
            }
            koreneStromu = koreneVypocet();
            for (int v : koreneStromu) {
                kody.emplace_back(kodStromAHU(v));
            }
        }

        Strom(const Hrany& hrany1, int n1)
        : hrany(hrany1)
        , n(n1) {
            for (int i = 0; i < n; i++) {
                graf[i] = std::vector<int>();
            }
            for (auto hrana : hrany) {
                int u = hrana[0];
                int v = hrana[1];
                graf[u].push_back(v);
                graf[v].push_back(u);
            }
            koreneStromu = koreneVypocet();
            for (int v : koreneStromu) {
                kody.emplace_back(kodStromAHU(v));
            }
            
        }

        int pocetVrcholov() {
            return n;
        }

        const Hrany& hranyStromu() {
            return hrany;
        }

        const std::vector<int>& korene() {
            return koreneStromu;
        }

        const std::vector<std::string>& kodyAHU() {
            return kody;
        }
        
};