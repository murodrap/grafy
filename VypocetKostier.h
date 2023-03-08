#pragma once
#include <stdio.h>
#include <vector>
#include <climits>
#include <string>


class VypocetKostier
{
    static double maxH(const std::vector<std::vector<double>>& hodnoty);
    using Matica = std::vector<std::vector<double>>;
    static long long gauss(Matica& matica, int n);
    static unsigned long long kofaktor(Matica& matica, int n, int r, int s);
    
public:
    
    using Hrany = std::vector<std::vector<int>>;
    static unsigned long long celkovyVypocet(const Hrany& hrany, int reg, int n);
};