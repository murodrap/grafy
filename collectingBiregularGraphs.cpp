#include <stdio.h>
#include <vector>
#include <map>
#include <climits>
#include <string>
#include <sstream>
#include <cmath>
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex> 

#include "collectingBiregularGraphs.h"
#include "collectingRegularGraphs.h"

/**
 * writes the final results to output file
 */
void ColBiregular::writeToFile() {

    std::stringstream nameOfFIle;
    nameOfFIle << "maxMinBireg" << reg << "-" << n << "-" << reg2 << "-" << numberOfFiles << ".txt";
    std::ofstream file2;
    file2.open (nameOfFIle.str());
    if (file2.is_open()) {
        graphsToFile("min", minK, minG, file2);
        graphsToFile("max", maxK, maxG, file2);
        file2.close();
    }
    else {
        std::cout << "Falied to open output file and to write the results";
    }
    
}