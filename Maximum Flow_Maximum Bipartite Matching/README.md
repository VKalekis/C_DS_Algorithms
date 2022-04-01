Maximum flow in Graph and Maximum Matching for Bipartite Graph using the Ford-Fulkerson algorithm.
The graphs are stored in a Sparse Array data structure.

Contains:
- algorithms.c and algorithms.h : Contains the algorithms used during the execution of the program.
- SparseArray.c and SparseArray.h : Sparse Array implementation and header file
- queue.c, queue.h : Queue implementation and header file
- menu.c, menu.exe : The main .c file, inserts edges in Sparse Array for each Graph and runs the corresponding algorithm.
- makefile : Useful for compiling and creating menu.exe. 
- inputEdgesFF.txt : Mass-inserts edges in Sparse Array for finding Maximum Flow in Graph. 
- inputEdgesBiparite.txt : Mass-inserts edges in Sparse Array for finding Maximum Matching for Bipartite Graph. 

Compile with either "gcc -o menu menu.c SparseArray.c queue.c algorithms.c" or by using the makefile.
		 