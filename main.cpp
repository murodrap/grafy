#include <stdio.h>
#include <iostream>
#include "spracovanie.h"
#include "VypocetKostier.h"


int main(int argc, char *argv[])
{
    
    SpracujCele* spr = new SpracujCele(std::atoi(argv[2]), std::atoi(argv[1]));
    spr->celySubor();
    
    return 0;
}