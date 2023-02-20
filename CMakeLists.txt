cmake_minimum_required(VERSION 3.22)

SET(CMAKE_INSTALL_PREFIX .)

project(pocitanieKostier
    DESCRIPTION "bla"
    LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

include_directories(
    /home/terezia/oneTbbInstallation/include
)
  
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(pocitanieKostier
    main.cpp
    spracovanie.cpp
    VypocetKostier.cpp)

target_link_directories(pocitanieKostier
    PUBLIC /home/terezia/oneTbbInstallation/lib
    
)

target_link_libraries(pocitanieKostier
    tbb

)



install(TARGETS pocitanieKostier DESTINATION bin)

