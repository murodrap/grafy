#include <stdio.h>
#include <iostream>
#include "spracovanie.h"
#include "VypocetKostier.h"


int main(int argc, char *argv[])
{
    /*
    
    std::vector<std::vector<int>> s;// = std::vector<float*>();
    
    for (int u = 0; u < 4; u++) {
        for (int v = u+1; v < 4; v ++) {
            std::vector<int> hrana(2);
            hrana.at(0) = u;
            hrana.at(1) = v;
            s.push_back(hrana);
        }
    }
    std::vector<std::string> vrch4;
    vrch4.push_back("1 : 2 3 4");
    vrch4.push_back("2 : 1 3 4");
    vrch4.push_back("3 : 1 2 4");
    vrch4.push_back("4 : 1 2 3");
    std::cout << VypocetKostier::celkovyVypocet(s, 3, 4) << "\n";

    int c = 5;
    int k = 2;
    int vvp = c;
    int vvd = 2*c;
    std::vector<std::vector<int>> hrany;
    int  posun = k;
    for (int i = 0; i < c; i++) {
        std::vector<int> h{i, (i+1)%c};
        std::vector<int> h2{i, i+c};
        std::vector<int> h3{i+c, (i+c+posun)%c + vvp};
        hrany.push_back(h); 
        hrany.push_back(h2);
        hrany.push_back(h3);
    }
    //for (std::vector<int> h : hrany) {
     //   std::cout << h.at(0) << " " << h.at(1) << "\n";
    //}
    //std::cout << VypocetKostier::celkovyVypocet(hrany, 3, 10);

    std::vector<std::vector<int>> zlyGraf;
    zlyGraf.push_back(std::vector<int>{0,1});
    zlyGraf.push_back(std::vector<int>{0,2});
    zlyGraf.push_back(std::vector<int>{0,3});
    zlyGraf.push_back(std::vector<int>{1,2});
    zlyGraf.push_back(std::vector<int>{1,3});
    zlyGraf.push_back(std::vector<int>{2,4});
    zlyGraf.push_back(std::vector<int>{3,4});
    zlyGraf.push_back(std::vector<int>{4,5});
    zlyGraf.push_back(std::vector<int>{5,6});
    zlyGraf.push_back(std::vector<int>{5,7});
    zlyGraf.push_back(std::vector<int>{6,7});
    zlyGraf.push_back(std::vector<int>{6,8});
    zlyGraf.push_back(std::vector<int>{7,8});
    zlyGraf.push_back(std::vector<int>{8,9});
    zlyGraf.push_back(std::vector<int>{9,10});
    zlyGraf.push_back(std::vector<int>{9,11});
    zlyGraf.push_back(std::vector<int>{10,11});
    zlyGraf.push_back(std::vector<int>{10,12});
    zlyGraf.push_back(std::vector<int>{11,13});
    zlyGraf.push_back(std::vector<int>{12,14});
    zlyGraf.push_back(std::vector<int>{12,15});
    zlyGraf.push_back(std::vector<int>{13,16});
    zlyGraf.push_back(std::vector<int>{13,17});
    zlyGraf.push_back(std::vector<int>{14,15});
    zlyGraf.push_back(std::vector<int>{14,16});
    zlyGraf.push_back(std::vector<int>{15,16});
    zlyGraf.push_back(std::vector<int>{17,18});
    zlyGraf.push_back(std::vector<int>{17,19});
    zlyGraf.push_back(std::vector<int>{18,20});
    zlyGraf.push_back(std::vector<int>{18,21});
    zlyGraf.push_back(std::vector<int>{19,20});
    zlyGraf.push_back(std::vector<int>{19,21});
    zlyGraf.push_back(std::vector<int>{20,21});
    //std::cout << VypocetKostier::celkovyVypocet(zlyGraf, 3, 22) << "\n";
    */


    SpracujCele* spr = new SpracujCele("gs.txt", std::atoi(argv[2]), std::atoi(argv[1]), 7319447);
    spr->celySubor();
    //std::cout << "najvacsie :: " << VypocetKostier::celkovyVypocet(spr->spracujGraf(vrch4), 3, 4) << "\n";
    //using Hrany = std::vector<std::vector<int>>;
    
    return 0;
}