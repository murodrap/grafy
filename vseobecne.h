#pragma once
#include <stdio.h>
#include <vector>
#include <string>

#include "VypocetKostier.h"

using Hrany = std::vector<std::vector<int>>;

class VseobecneFunkcie
{
    static bool havelHakimi(int n1, int k1, int n2, int k2);
    static Hrany stringNaHrany(const std::string& zoznamHran);

    public:
        static bool existujeGraf(int n1, int k1, int n2, int k2);
        static unsigned long long pocetKostier(const Hrany& hrany, int reg, int n);
        static unsigned long long pocetKostier(const std::string& hrany, int reg, int n);
        static unsigned long generovanieKostier(const Hrany& hrany, int n, const std::string& suborDo); 
        static unsigned long generovanieKostier(const std::string& hrany, int n, const std::string& suborDo); 
};