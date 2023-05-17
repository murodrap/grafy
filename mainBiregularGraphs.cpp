#include <stdio.h>
#include <iostream>
#include <chrono>

#include "processingBiergularGraphs.h"
#include "processingRegularGraphs.h"

int main(int argc, char *argv[])
{
    std::string file;
    int n;
    int k;
    int k2;
    if (argc == 4) {
        n = std::atoi(argv[1]);
        k = std::atoi(argv[2]);
        k2 = std::atoi(argv[3]);
        file = "maxMinBireg" +  std::to_string(k) + "-" +  std::to_string(n) + "-" + std::to_string(k2) + ".txt";
    }
    else if (argc == 5) {
        std::string s(argv[1]);
        file = s;
        n = std::atoi(argv[2]);
        k = std::atoi(argv[3]);
        k2 = std::atoi(argv[4]);
    }
    else {
        std::cout << "Incorrect number of arguments" << std::endl;
        return 1;
    }

    ProcBiregular pro(file, k, n, k2);

    auto start = std::chrono::high_resolution_clock::now();
    pro.processAll();
    auto end = std::chrono::high_resolution_clock::now();
    auto processingTime = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    std::cout << "Processing finished after " << processingTime << " seconds\n";
}