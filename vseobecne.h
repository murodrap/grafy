#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include <map>

#include "VypocetKostier.h"

using Hrany = std::vector<std::vector<int>>;
using AdjList = std::map<int, std::vector<int>>;

class VseobecneFunkcie
{
    static bool havelHakimi(int n1, int k1, int n2, int k2);
    static Hrany stringNaHrany(std::string& zoznamHran);
    static AdjList stringNaAdjList(std::string& zoznamHran, int n);
    static bool izomorfneGrafy(const AdjList& g1, int n1, const AdjList& g2, int n2);
    
    public:
        
        static bool existujeGraf(int n1, int k1, int n2, int k2);
        static unsigned long long pocetKostier(const Hrany& hrany, int reg, int n) {
            VypocetKostier poc = VypocetKostier(n, reg);
            unsigned long long kostier = poc.celkovyVypocet(hrany);
            poc.koniec();
            return kostier;
            
        }
        static unsigned long long pocetKostier(std::string& hrany, int reg, int n) {
            return pocetKostier(stringNaHrany(hrany), reg, n);
        }
        static bool izomorfneGrafy(std::string& g1, int n1, std::string& g2, int n2);
        static unsigned long generovanieKostier(const Hrany& hrany, int n, const std::string& suborDo); 
        static unsigned long generovanieKostier(const std::string& hrany, int n, const std::string& suborDo); 
};