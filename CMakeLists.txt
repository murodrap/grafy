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

add_executable(spanningTreesRegular
    mainRegularGraphs.cpp
    processingRegularGraphs.cpp
    spanningTreeCounting.cpp)

add_executable(spanningTreesBiregular
    mainBiregularGraphs.cpp
    processingBiregularGraphs.cpp
    spanningTreeCounting.cpp
    generalGraphs.cpp
    isomorphismAHU.cpp
    unlabeledSpanningTrees.cpp
    processingRegularGraphs.cpp)


#add_executable(kostryTriedy
#    mainTriedy.cpp
#    spracovanieTriedy.cpp
#    unlabeledSpanningTrees.cpp
#    isomorphismAHU.cpp
#    processingRegularGraphs.cpp
#    vypocetKostier)

add_executable(resultsRegular
    mainCollectingRegularGraphs.cpp
    collectingRegularGraphs.cpp)

add_executable(resultsBiregular
    mainCollectingBiregularGraphs.cpp
    collectingRegularGraphs.cpp
    collectingBiregularGraphs.cpp)

#add_executable(zberTriedy
#    mainZberTriedy.cpp
#    collectingRegularGraphs.cpp
#    zberTriedy.cpp)

add_executable(graphsFunctions
    mainGeneralGraphs.cpp
    generalGraphs.cpp
    spanningTreeCounting.cpp
    isomorphismAHU.cpp
    unlabeledSpanningTrees.cpp)

#add_executable(generovanie
#    mainGenerovanie.cpp
#    generalGraphs.cpp
#    spanningTreeCounting.cpp
#    generovanie.cpp
#    isomorphismAHU.cpp
#    unlabeledSpanningTrees.cpp)

install(TARGETS spanningTreesRegular resultsRegular spanningTreesBiregular resultsBiregular graphsFunctions DESTINATION bin)
