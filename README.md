All programs are designed to run in command line.

To build executable files from the source code, we first need to run "cmake ." in a directory that which contains the source code or "cmake .." in a directory withing this directory. Then we run make install, this will create ./bin directory with all executable files which are specified in CMakeLists.txt.  Except from graphsFunctions, the path to the rest of executables should be added to PATH variable.
Most of the programs require the use of genreg, which can be acquire for example from https://sourceforge.net/projects/genreg/. It should be stored under the name GenReg and also the path to this program should be added to PATH.

graphsFunctions is run with no arguments, it has command line interfae with simple menu with an overview of the functionality it offers. The graph that user passes to the running program are represented as edge lists, where vertices are labeled from 0 to n-1 (n is the number of vertices in the grap). The order of edges can be arbitrary, but the edge list should have this format:

[(0, 1), (0, 2), (0, 3), (1, 2)]

Among the source code, there are bash scripts for generating and processing regular graphs. They should be set to be executable by users by adding execute permissions to each file. 
Here are command runnint the scripts with needed arguments

**regularSerial n k**
-generates all k-regular graphs on n vertices, stores the graphs with the least and most spanning trees to maxMinReg<k>-<n>.txt

**regularParalel j n k**
-the same functionality as the previous script, only the generation and processing is split into j parts, the results are written to maxMinReg<k>-<n>-<j>.txt

**biregularSerial n k k2**
-generates all biregular graphs on n+1 vertices where n vertices are of degree k and one is of degree k2, stores the graphs with the least and most spanning trees to maxMinBireg<k>-<n>-<k2>.txt

**biregularParalel j n k k2**
-the same functionality as the previous script, only the generation and processing is split into j parts, the results are written to maxMinBireg<k>-<n>-<k2>-<j>.txt

**regularGirthSerial n k t**
-generates all k-regular graphs on n vertices with girst at least t, stores the graphs with the least and most spanning trees to maxMinRegGirth<k>-<n>-<t>.txt

**regularGirthParalel j n k t**
-the same functionality as the previous script, only the generation and processing is split into j parts, the results are written to maxMinRegGirth<k>-<n>-<j>.txt

The functionality of these scripts is described in detail in the Implementaion chapter of the bachelor thesis.


