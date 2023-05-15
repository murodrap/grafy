#pragma once
#include <stdio.h>
#include <vector>
#include <string>
#include <map>

#include "vypocetKostier.h"
#include "vsetkyKostry.h"
#include "izomorfizmus.h"

using Hrany = std::vector<std::vector<int>>;
using AdjList = std::map<int, std::vector<int>>;

class VseobecneFunkcie
{
    static bool havelHakimi(int n1, int k1, int n2, int k2);
    static Hrany stringNaHrany(std::string& zoznamHran);
    static AdjList stringNaAdjList(std::string& zoznamHran, int n);
    static bool izomorfneGrafy(const AdjList& g1, int n1, const AdjList& g2, int n2);
    static void vypisGraf(const Hrany& graf);
    
    public:
        
        static bool existujeGraf(int n1, int k1, int n2, int k2);
        static long long pocetKostier(const Hrany& hrany, int reg, int n) {
            VypocetKostier poc = VypocetKostier(n, reg);
            long long kostier = poc.celkovyVypocet(hrany);
            poc.koniec();
            return kostier;
            
        }
        static long long pocetKostier(std::string& hrany, int reg, int n) {
            return pocetKostier(stringNaHrany(hrany), reg, n);
        }
        static bool izomorfneGrafy(std::string& g1, int n1, std::string& g2, int n2);

        static Hrany kostraBFS(std::string& hrany, int n) {
            return kostraBFS(stringNaAdjList(hrany, n), n);
        }
        static Hrany kostraBFS(const AdjList& graf, int n);

        static const std::map<Strom*, int> generovanieKostier(const Hrany& hrany, int n, const std::string& suborDo) {
            Onete o = Onete(n, hrany.size());

            const std::map<Strom*, int> triedy = o.generovanieKostier(hrany);
            o.zapisDoSuboru(suborDo);
            return triedy;
        }
        static const std::map<Strom*, int> generovanieKostier(std::string& hrany, int n, const std::string& suborDo) {
            return generovanieKostier(stringNaHrany(hrany), n, suborDo);
        }
        static void porovnamieKostier(std::string& g1, int n1, std::string& g2, int n2);

        
};