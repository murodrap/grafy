#include <stdio.h>
#include <iostream>
#include <chrono>

#include "spracovanie.h"
#include "VypocetKostier.h"

inline std::string
  to_string2(__int128 __val)
  { return __gnu_cxx::__to_xstring<std::string>(&std::vsnprintf,
                       4 * sizeof(__int128),
                       "%lll", __val); }

std::ostream& operator<<(std::ostream& o, const __int128& x) {
    if (x == std::numeric_limits<__int128>::min()) return o << "-170141183460469231731687303715884105728";
    if (x < 0) return o << "-" << -x;
    if (x < 10) return o << (char)(x + '0');
    return o << x / 10 << (char)(x % 10 + '0');
}

int main(int argc, char *argv[])
{
    //unsigned long long k = VypocetKostier::celkovyVypocet({{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 4}, {2, 5}, {3, 4}, {3, 6}, {4, 7}, {5, 8}, {5, 9}, {6, 8}, {6, 10}, {7, 10}, {7, 11}, {8, 12}, {9, 11}, {9, 13}, {10, 14}, {11, 15}, {12, 13}, {12, 16}, {13, 17}, {14, 18}, {14, 19}, {15, 18}, {15, 20}, {16, 21}, {16, 22}, {17, 23}, {17, 24}, {18, 25}, {19, 21}, {19, 23}, {20, 22}, {20, 24}, {21, 26}, {22, 27}, {23, 27}, {24, 26}, {25, 26}, {25, 27}}, 3, 28);
    
    //std::cout << k << std::endl;
    
    if (argc != 4) {
        std::cout << "zly pocet argumentov\n";
        return 1;
    }

    std::string subor(argv[1]);
    SpracujCele spr(subor, std::atoi(argv[3]), std::atoi(argv[2]));

    auto zaciatok = std::chrono::high_resolution_clock::now();
    spr.celySubor();
    auto koniec = std::chrono::high_resolution_clock::now();
    auto dlzka = std::chrono::duration_cast<std::chrono::seconds>(koniec - zaciatok).count();

    std::cout << "spracovanie bolo ukoncene po " << dlzka << " sekundach\n";
}