#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "VypocetKostier.h"

using Matica = std::vector<std::vector<double>>;
using Hrany = std::vector<std::vector<int>>;

double VypocetKostier::maxH(const std::vector<std::vector<double>>& hodnoty) {

    double najdene[2] {0., 0.};
    for (const std::vector<double>& h : hodnoty) {
        
        double p = h[0];
        double d = h[1];
        
        if (p > najdene[0]) {
            najdene[0] = p;
            najdene[1] = d;
        }
        else if (p == najdene[0] && d > najdene[1]) {
            najdene[0] = p;
            najdene[1] = d;
        }
   }

    return najdene[1];
}


long VypocetKostier::gauss(Matica& matica, int n) {
    int r1 = 0;
    int s1 = 0;
    int nas = 0;


    while (r1 < n && s1 < n) {
            double iMax;
            std::vector<std::vector<double>> hodnoty(n-r1);

            for (int i = r1; i < n; i++) {
                hodnoty[i-r1] = {(double)std::abs(matica[i][s1]), (double)i};
                // //vnutro.reserve;
                // vnutro[0] = (double)std::abs(matica[i][s1]);
                // vnutro[1] = (double)i;
                // hodnoty[i-r1] = vnutro;
            }
            iMax = maxH(hodnoty);
            
            if (matica[iMax][s1] == 0) { // r1 15 s1 15
                s1++;
            }

            else {
                std::swap(matica[r1], matica[iMax]);
                //if (r1 == 6 || r1 == 7 || iMax == 6 || iMax == 7) {
                    //std::cout <<  r1 << " " << s1 <<" 76: " << matica[7][6] << " 66: " << matica[6][6] << " iMax "<< iMax <<"\n";
                //}
                //std::cout << r1 << " " << s1 << " imax: " << iMax <<  " " << matica[r1] << " " << matica[iMax] <<"\n";
                nas *= -1;
                //std::cout <<"d " << r1 << " " << s1 << "\n";

                for (int i = r1+1; i < n; i++) {
                    double f = matica[i][s1] / matica[r1][s1];
                    matica[i][s1] = 0.;
                    //std::cout << "  " << i << " " << s1 <<  " f: "  << f <<"\n";
                    for (int j = s1+1; j < n; j++) {
                        //std::cout << "    j: " << j << " r1j: " << matica[r1][j] << "\n";
                        matica[i][j] -= matica[r1][j] * f;
                        //if ((i == 7 && j == 6) || (i == 6 && j == 6)) {
                            //std::cout <<  r1 << " " << s1 <<" 76: " << matica[7][6] << " 66: " << matica[6][6] << " ij " << i << " " << j << "\n";
                        //}
                        
                        //std::cout << "      " << matica[i][j] << "\n";
                    }
                }

            }
            r1++;
            s1++;
        }
            
        double vysl = 1.;
        for (int i = 0; i < n; i++) {
            vysl *= matica[i][i];
            //std::cout << "a " << vysl << "\n";
        }

    return abs(round(vysl));


}

long VypocetKostier::kofaktor(Matica& matica, int n, int r, int s) {
    return (long) (pow(-1, r+s) * VypocetKostier::gauss(matica, n-1));
}

long VypocetKostier::celkovyVypocet(const Hrany& hrany, int reg, int n) {
    std::vector<std::vector<double>> matica(n-1);
    for (int i= 0; i < n-1; i++) {
        std::vector<double> riadok(n-1);
        matica[i] = riadok;

    }
   
    //pre neregulare grafy doplnit zistovanie stupnov vrchov
    for (const std::vector<int>& hrana : hrany) {
        int u = hrana[0]-1;
        int v = hrana[1]-1;
        if (v >= 0 && u >= 0) {
            matica[u][v] = -1.;
            matica[v][u] = -1.;
        }

    }
    for (int r = 0; r < n-1; r++) {
        matica[r][r] = (double)reg;
    }


    return VypocetKostier::kofaktor(matica, n, 0, 0);
}