All programs are designed to run in command line.

To build executable files from the source code, we first need to run "cmake ." in a directory that which contains the source code or "cmake .." in a directory withing this directory. Then we run make install, this will create ./bin directory with all executable files which are specified in CMakeLists.txt.  Except from graphsFunctions, the path to the rest of executables should be added to PATH variable.
Most of the programs require the use of genreg, which can be acquire for example from https://sourceforge.net/projects/genreg/. It should be stored under the name GenReg and also the path to this program should be added to PATH.

graphsFunctions is run with no arguments and its functionality is described in the bachelor thesis. The graph that user passes to the console interface of the running program are represented as edge lists, where vertices are labeled from 0 to n-1 (n is the number of vertices in the grap). The order of edges can be arbitrary, but the edge list should have this format:

[(0, 1), (0, 2), (0, 3), (1, 2)]

Among the source code, there are bash scripts that cover the rest of the functionality. They should be set to be executable by users by adding execute permissions to each file. These scripts are run with arguments which are described in detail, along with their functionality and output, in the Implementaion chapter of the bachelor thesis.


