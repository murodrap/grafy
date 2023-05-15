#include <stdio.h>
#include <vector>
#include <climits>
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string.h>
#include "vypocetKostier.h"

using Matica = std::vector<std::vector<double>>;
using Hrany = std::vector<std::vector<int>>;

double VypocetKostier::maxH(int pocet) {

    double najdene[2] {0., 0.};
    for (int i = 0; i < pocet; i++) {
        
        double p = dvojiceHodnot[i][0];
        double d = dvojiceHodnot[i][1];
        
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


long long VypocetKostier::gauss(int n) {
    int r1 = 0;
    int s1 = 0;
    int nas = 0;


    while (r1 < n && s1 < n) {
            double iMax;

            std::vector<std::vector<double>> hodnoty(n-r1);

            for (int i = r1; i < n; i++) {
                dvojiceHodnot[i-r1][0] = (double)std::abs(matica[i][s1]);
                dvojiceHodnot[i-r1][1] = (double)i;
            }
            iMax = maxH(n - r1);
            
            if (matica[(int)iMax][s1] == 0) {
                s1++;
            }

            else {
                std::swap(matica[r1], matica[(int)iMax]);
                nas *= -1;

                for (int i = r1+1; i < n; i++) {
                    double f = matica[i][s1] / matica[r1][s1];
                    matica[i][s1] = 0.;
                    for (int j = s1+1; j < n; j++) {
                        matica[i][j] -= matica[r1][j] * f;
                    }
                }

            }
            r1++;
            s1++;
        }
            
        double vysl = 1.;
        for (int i = 0; i < n; i++) {
            vysl *= matica[i][i];
        }

    return llabs(llround(vysl));


}

long long VypocetKostier::kofaktor(int n, int r, int s) {
    return (long long) (pow(-1, r+s) * VypocetKostier::gauss(n-1));
}

long long VypocetKostier::celkovyVypocet(const Hrany& hrany) {
    for (int i= 0; i < n-1; i++) {
        memset(matica[i], 0, (n - 1)*sizeof(*matica[i]));
    }
   

    for (const std::vector<int>& hrana : hrany) {
        int u = hrana[0]-1;
        int v = hrana[1]-1;
        if (v >= 0 && u >= 0) {
            matica[u][v] = -1.;
            matica[v][u] = -1.;
        }
        if (!reg) { 
            if (u >= 0) matica[u][u]++;
            if (v >= 0) matica[v][v]++;
        }

    }

    if (reg) {
        for (int r = 0; r < n-1; r++) {
            matica[r][r] = (double)reg;
        }
    }


    return VypocetKostier::kofaktor(n, 0, 0);
}