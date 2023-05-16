#include <stdio.h>
#include <vector>
#include <climits>
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string.h>
#include "spanningTreeCounting.h"

using Matica = std::vector<std::vector<double>>;
using Edges = std::vector<std::vector<int>>;

double SpanningTreeCounter::maxValue(int number) {

    double najdene[2] {0., 0.};
    for (int i = 0; i < number; i++) {
        
        double p = pairs[i][0];
        double d = pairs[i][1];
        
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


long long SpanningTreeCounter::gauss(int n) {
    int r1 = 0;
    int s1 = 0;
    int nas = 0;


    while (r1 < n && s1 < n) {
            double iMax;

            std::vector<std::vector<double>> hodnoty(n-r1);

            for (int i = r1; i < n; i++) {
                pairs[i-r1][0] = (double)std::abs(matrix[i][s1]);
                pairs[i-r1][1] = (double)i;
            }
            iMax = maxValue(n - r1);
            
            if (matrix[(int)iMax][s1] == 0) {
                s1++;
            }

            else {
                std::swap(matrix[r1], matrix[(int)iMax]);
                nas *= -1;

                for (int i = r1+1; i < n; i++) {
                    double f = matrix[i][s1] / matrix[r1][s1];
                    matrix[i][s1] = 0.;
                    for (int j = s1+1; j < n; j++) {
                        matrix[i][j] -= matrix[r1][j] * f;
                    }
                }

            }
            r1++;
            s1++;
        }
            
        double vysl = 1.;
        for (int i = 0; i < n; i++) {
            vysl *= matrix[i][i];
        }

    return llabs(llround(vysl));


}

long long SpanningTreeCounter::kofaktor(int n, int r, int s) {
    return (long long) (pow(-1, r+s) * SpanningTreeCounter::gauss(n-1));
}

long long SpanningTreeCounter::countForGraph(const Edges& edges) {
    for (int i= 0; i < n-1; i++) {
        memset(matrix[i], 0, (n - 1)*sizeof(*matrix[i]));
    }
   

    for (const std::vector<int>& edge : edges) {
        int u = edge[0]-1;
        int v = edge[1]-1;
        if (v >= 0 && u >= 0) {
            matrix[u][v] = -1.;
            matrix[v][u] = -1.;
        }
        if (!reg) { 
            if (u >= 0) matrix[u][u]++;
            if (v >= 0) matrix[v][v]++;
        }

    }

    if (reg) {
        for (int r = 0; r < n-1; r++) {
            matrix[r][r] = (double)reg;
        }
    }


    return SpanningTreeCounter::kofaktor(n, 0, 0);
}