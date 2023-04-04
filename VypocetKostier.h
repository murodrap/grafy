#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>


class VypocetKostier
{
    int n;
    int reg;
    double **matica = nullptr;
    double **dvojiceHodnot = nullptr;

    double maxH(int pocet);
    //using Matica = double[][];
    long long gauss(int n);
    unsigned long long kofaktor(int n, int r, int s);
    
public:
    
    using Hrany = std::vector<std::vector<int>>;
    unsigned long long celkovyVypocet(const Hrany& hrany);
    VypocetKostier(int n2, int reg2)
    : n(n2)
    , reg(reg2)
    {
        dvojiceHodnot = new double*[n - 1];
        matica = new double*[n-1];
        for (int i = 0; i < n - 1; i++) {
            dvojiceHodnot[i] = new double[2];
            matica[i] = new double[n - 1];
        }

    }
    void koniec() {
        for (int i = 0; i < n - 1; i++) {
            delete matica[i];
            delete dvojiceHodnot[i];
        }
        delete matica;
        delete dvojiceHodnot;
    }
};