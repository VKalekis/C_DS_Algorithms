#ifndef SparseArray_h
#define SparseArray_h



typedef struct edge *pt;
struct edge
{
    int i, j, inSpanningTree;
    pt l, r, u, d;
};

typedef struct node *np;
struct node
{
    int key, dist, occupied, isLeaf;
    char color;
    np p;
};

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
void insertFromFile(int sel);

/* Searches for the existence of an edge with i = data_i and j = data_j. 
    If such an edge doesn't exist, it inserts a new edge with the forementioned data. Otherwise, it aborts. O(E) */
void searchAndInsertEdge(int data_i, int data_j);




// Asks for user input for i,j and either deletes an edge i-j (sel = 0) or edges i-j and j-i (sel = 1). O(E)
void deleteSelections(int sel);

// Finds and deletes the edge with data i = data_i, j = data_j. Ο(Ε)
void deleteEdge(int data_i, int data_j);



/* Runs Breadth First Search on the graph using the Sparse Array. Prints the paths from the leaves to the root of the tree 
    and marks all the edges which belong to the Spanning Tree of the graph. Returns 1. O(V+E) */
int BFS();


/* Finds circles in the graph represented by the Sparse Array. The function finds the edges which don't belong in the Spanning Tree and finds the paths to the root 
    from the two nodes connected by the edge. This edge will be a part of the circle since all the other edges belong to a tree. Afterwards, it finds the circle using the function 
    unionandintersection, passing as arguments the two paths from the nodes to the root of the Spanning Tree. If ranbfs = 0, BFS has not yet run and this function calls BFS(). 
    If ranbfs = 1, BFS has already run and the program asks the user whether to run a new BFS or not.
    O(E) for finding the circles for 1 edge, O(E^2) for finding the circles for every edge not in the Spanning Tree. */
void findCircles(int ranbfs);


#endif
