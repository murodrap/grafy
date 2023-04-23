cmake_minimum_required(VERSION 3.22)

SET(CMAKE_INSTALL_PREFIX .)

project(pocitanieKostier
    DESCRIPTION "bla"
    LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
  
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(kostryRegularne
    mainRegularne.cpp
    spracovanieRegularne.cpp
    vypocetKostier.cpp)

add_executable(kostryBiregularne
    mainBiregularne.cpp
    spracovanieBiregularne.cpp
    vypocetKostier.cpp
    vseobecne.cpp
    izomorfizmus.cpp
    vsetkyKostry.cpp
    spracovanieRegularne.cpp)

add_executable(kostryTriedy
    mainTriedy.cpp
    spracovanieTriedy.cpp
    vsetkyKostry.cpp
    izomorfizmus.cpp
    spracovanieRegularne.cpp
    vypocetKostier)

add_executable(zberRegularne
    mainZberRegularne.cpp
    zberRegularne.cpp)

add_executable(zberBiregularne
    mainZberBiregularne.cpp
    zberRegularne.cpp
    zberBiregularne.cpp)

add_executable(grafyFunkcie
    mainVseobecne.cpp
    vseobecne.cpp
    vypocetKostier.cpp
    izomorfizmus.cpp
    vsetkyKostry.cpp)

add_executable(generovanie
    mainGenerovanie.cpp
    vseobecne.cpp
    vypocetKostier.cpp
    generovanie.cpp
    izomorfizmus.cpp
    vsetkyKostry.cpp)

install(TARGETS kostryRegularne zberRegularne kostryBiregularne kostryTriedy zberBiregularne generovanie grafyFunkcie DESTINATION bin)
