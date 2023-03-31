#include <stdio.h>
#include <vector>
#include <string>
#include <bits/stdc++.h>

#include "VypocetKostier.h"
#include "vseobecne.h"

bool VseobecneFunkcie::havelHakimi(int n1, int k1, int n2, int k2) {
    std::vector<int> stupne;
    for (int i  = 0; i < n1; i++) {
        stupne.push_back(k1);
    }
    for (int i  = 0; i < n2; i++) {
        stupne.push_back(k2);
    }
    std::sort(stupne.begin(), stupne.end(), std::greater<int>());

    while (true){
        if (stupne[0] == 0) {
            break;
        }
        
        for (int i = 1; i <= stupne[0]; i++) {
            if (stupne[i] == 0) {
                return false;
            }
            stupne[i] -= 1;
        }
        stupne[0] = 0;
        std::sort(stupne.begin(), stupne.end(), std::greater<int>());
    }
    return true;
}

bool VseobecneFunkcie::existujeGraf(int n1, int k1, int n2, int k2){
    if (k1 > n1 + n2 || k2 > n1 + n2) {
        std::cout << "nie je mozne vytvorit graf bez nasobnych hran\n";
        return false;
    }
    if ((n1 * k1 + n2 * k2) % 2) {
        std::cout << "neparny pocet hran\n";
        return false;
    }
    if (!havelHakimi(n1, k2, n2, k2)) {
        std::cout << "nesedi havel hakimi\n";
        return false;
    }
    return true;
}

Hrany VseobecneFunkcie::stringNaHrany(const std::string& zoznamHran) {
    Hrany hrany;
    std::istringstream iss(zoznamHran);
    std::string znaky;
    int vrchol1;
    int vrchol2;
    bool zacataHrana = false;
    while (true) {
        iss >> znaky;
        if (znaky.empty()) {
            break;
        }
        iss >> vrchol1;
        iss >> znaky;
        iss >> vrchol1;
        hrany.push_back({vrchol1, vrchol2});
    }
    return hrany;
}