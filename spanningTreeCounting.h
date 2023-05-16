#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>


class SpanningTreeCounter
{
    int n;
    int reg;
    double **matrix = nullptr;
    double **pairs = nullptr;

    double maxValue(int number);
    //using Matica = double[][];
    long long gauss(int n);
    long long kofaktor(int n, int r, int s);
    
public:
    
    using Edges = std::vector<std::vector<int>>;
    long long countForGraph(const Edges& edges);
    SpanningTreeCounter(int n2, int reg2)
    : n(n2)
    , reg(reg2)
    {
        pairs = new double*[n - 1];
        matrix = new double*[n-1];
        for (int i = 0; i < n - 1; i++) {
            pairs[i] = new double[2];
            matrix[i] = new double[n - 1];
        }

    }
    void koniec() {
        for (int i = 0; i < n - 1; i++) {
            delete matrix[i];
            delete pairs[i];
        }
        delete matrix;
        delete pairs;
    }
};