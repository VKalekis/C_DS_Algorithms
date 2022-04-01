#ifndef SparseArray_h
#define SparseArray_h

#define ARRAY_SIZE 30
#include <stdio.h>

typedef struct edge* pt;
struct edge {
    int i, j, flow, residualcapacity, inOriginalGraph, inSpanningTree;
    pt l, r, u, d;
};

typedef struct node* np;
struct node {
    int key, dist, occupied, isLeaf;
    char color;
    np p;
};

//Size of array = ARRAY_SIZE+2 for accounting supersource/supersink nodes for Maximum Flow in Bipartite Graph
extern pt rows[ARRAY_SIZE + 2], cols[ARRAY_SIZE + 2];
extern struct node nodes[ARRAY_SIZE + 2];

// Initializes node list. O(V)
void initializeNodeList();

// Print the array of nodes and the attributes of each node. O(V)
void printNodeList();

/* Prints Sparse Array by rows and columns.  O(V+E)
    sel = 0 for printing all edges
    sel = 1 for printing edges in Spanning Tree */
void printSparseArray(int sel);

/* Searches for the existence of an edge with i = data_i, j = data_j. 
    Returns 1 if exists such an edge and 0 otherwise. O(E) */
int search(int data_i, int data_j);

// Asks for user input for i,j and either inserts an edge i-j (sel = 0) or edges i-j and j-i (sel = 1). O(E)
void insertSelections(int sel);

// Inserts edges i-j (sel = 0) or i-j and j-i (sel = 1) from the file "inputEdges.txt" O(V+E)
void insertFromFile(char* filename, int sel);

/* Searches for the existence of an edge with i = data_i and j = data_j. 
    If such an edge doesn't exist, it inserts a new edge with the forementioned data. Otherwise, it aborts. O(E) */
void searchAndInsertEdge(int data_i, int data_j, int data_capacity, int data_inOriginalGraph);

// Asks for user input for i,j and either deletes an edge i-j (sel = 0) or edges i-j and j-i (sel = 1). O(E)
void deleteSelections(int sel);

// Finds and deletes the edge with data i = data_i, j = data_j. Ο(Ε)
void deleteEdge(int data_i, int data_j);

//Auxiliary function for outputting SparseArray at .txt file for Python visualizations.
void writetofile();

#endif
