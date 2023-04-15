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

add_executable(zberRegularne
    mainZberRegularne.cpp
    zberRegularne.cpp)

install(TARGETS kostryRegularne zberRegularne DESTINATION bin)
