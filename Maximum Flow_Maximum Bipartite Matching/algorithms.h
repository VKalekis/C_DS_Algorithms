#ifndef algorithms_h
#define algorithms_h

#include "SparseArray.h"
#include "queue.h"

/* Runs Breadth First Search on the graph using the Sparse Array. Prints the paths from the leaves to the root of the tree 
    and marks all the edges which belong to the Spanning Tree of the graph. Returns 1. O(V+E) */
int BFS(int s, int t, int offset);

/* Modified BFS used for determining if a graph is bipartite. Each node is colored either R or B, with the source s starting at R. 
Each R node colors its neighbors B and each B node colors its neighbors R, respectively. If the algorithm finds an edge which connects
two nodes with the same color, the graph is not bipartite and the algorithm terminates, returning 0. Otherwise, the algorithm returns 1
and the graph is bipartite. O(V+E) */
int bipartiteBFS(int s);

/*Run Edmonds Karp algorithm for finding maximum flow in graph. The user will have to provide the source and the sink of the flow.
The maximum flow is calculated by finding the augmenting path using BFS. It locates the edge with the minimum residual capacity and updates
the flow attribute and the residual capacity of every edge in the path with the min. residual capacity of the path. O(VE^2) 
*/
void EdmondsKarp();

/*Internal Function. Runs EdmondsKarp algorithm given source s, sink t and the extrarows attribute (extrarows = 0 for running Maximum flow 
on graph G, extrarows = 2 for running Maximum flow on bipartite graph) O(VE^2) */
void EdmondsKarpAlgorithm(int s, int t, int extrarows);

//Finds and return edge with attributes i = data_x j = data_j from Sparse Array. O(E)
pt findEdge(int data_i, int data_j);

/* Main algorithm for maximum bipartite matching, given an graph already inserted in the Sparse Array.
It determines if the graph is bipartite with bipartiteBFS. It creates the corresponding graph G' by using a supersource
and supersink node. We will use row/col 31 of the SparseArray for the supersource and row/col 32 for the supersink. Then, 
the algorithm runs EdmondsKarp with the following parameters: source 31, sink 32, extrarows 2, as we want to use the
32x32 Sparse Array and not the original 30x30. O(VE) */
void bipartitegraph();

#endif
