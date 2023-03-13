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

add_executable(pocitanieKostier
    main.cpp
    spracovanie.cpp
    VypocetKostier.cpp)

add_executable(zber
    mainZber.cpp
    zbieranieVysledkov.cpp)

install(TARGETS pocitanieKostier zber DESTINATION bin)

