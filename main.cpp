#include <stdio.h>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "spracovanie.h"
#include "VypocetKostier.h"


void vypisVektoru(const std::vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}
bool havelHakimi(int n, int k, int h) {
    std::vector<int> stupne;
    for (int i  = 0; i < n; i++) {
        stupne.push_back(k);
    }
    stupne.push_back(h);
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
        //vypisVektoru(stupne);
    }
    return true;
}

bool kontrolaExistencieGrafu(int n, int k, int h) {
    if (h <= 0) {
        std::cout << "nesuvisly graf\n";
        return false;
    }
    if (h > n) {
        std::cout << "nie je mozne vztvorit graf bez nasobnych hran\n";
        return false;
    }
    if ((n * k + h) % 2) {
        std::cout << "neparny pocet hran\n";
        return false;
    }
    if (!havelHakimi(n, k, h)) {
        std::cout << "nesedi havel hakimi\n";
        return false;
    }
    return true;
}


int main(int argc, char *argv[])
{
    int n = std::atoi(argv[1]);
    int k = std::atoi(argv[2]);
    int hodnota = std::atoi(argv[3]);
    if (!kontrolaExistencieGrafu(n, k, hodnota)) {
        std::cout << "NEexistuje vyhovujuci graf\n";
        return 1;
    }
    //else {
    //    return 1;
    //}
    SpracujCele* spr = new SpracujCele(k, n, hodnota);
    spr->celySubor();
    
    return 0;
}