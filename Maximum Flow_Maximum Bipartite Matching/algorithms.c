#include "SparseArray.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int BFS(int s, int t, int extrarows)
{
    int i, dequeued, rownum, root, found_t = 0;
    pt head;

    //Initialization
    for (i = 0; i < ARRAY_SIZE + extrarows; i++) {
        nodes[i].isLeaf = 0;
        if (nodes[i].occupied == 1) {
            if (nodes[i].key != s) {
                nodes[i].color = 'W';
                nodes[i].dist = -10;
                nodes[i].p = NULL;
            } else {
                nodes[i].color = 'G';
                nodes[i].dist = 0;
                nodes[i].p = NULL;
            }
        }
    }

    struct Queue q;
    newQueue(&q);
    enqueue(&q, s);

    while (isQueueEmpty(q) == 0) {

        dequeued = dequeue(&q);
        // printf("%d\n", dequeued);
        rownum = dequeued - 1;
        head = rows[rownum];

        while (head != NULL) {
            if ((nodes[head->j - 1].color == 'W') && (head->residualcapacity > 0)) {
                nodes[head->j - 1].color = 'G';
                nodes[head->j - 1].dist = nodes[rownum].dist + 1;
                nodes[head->j - 1].p = &nodes[rownum];
                nodes[rownum].isLeaf = 0;
                nodes[head->j - 1].isLeaf = 1;

                if (nodes[head->j - 1].key == nodes[t - 1].key) {
                    deleteQueue(&q);
                    found_t = 1;
                    break;
                }
                // printf("Enqueued: %d\n", head->j);
                enqueue(&q, head->j);
            }

            head = head->r;
        }
        //printf("Visited: %d - Distance: %d\n", nodes[rownum].key, nodes[rownum].dist);
        nodes[rownum].color = 'B';
    }

    return found_t;
}

pt findEdge(int data_i, int data_j)
{
    pt head = rows[data_i - 1];
    while (head != NULL) {
        if (head->j == data_j) {
            return head;
        }
        head = head->r;
    }
}

void EdmondsKarpAlgorithm(int s, int t, int extrarows)
{

    //Flow=0 is already initialized for each node.
    int maxflow = 0;

    struct node sink;
    int minrescapacity, edgerescapacity, count = 0;
    pt edge, symedge;

    while (BFS(s, t, extrarows) == 1) {

        //writetofile();

        sink = nodes[t - 1];
        printf("\nPath from sink to source:\n");

        printf("-----------------------\n");
        while (sink.p != NULL) {
            edge = findEdge((*(sink.p)).key, sink.key);
            edgerescapacity = edge->residualcapacity;

            if (count == 0) {
                count++;
                minrescapacity = edgerescapacity;
            } else {
                if (edgerescapacity < minrescapacity) {
                    minrescapacity = edgerescapacity;
                }
            }

            printf("%d -> ", sink.key);
            sink = *(sink.p);
        }
        printf("%d\n", sink.key);

        printf("Minimum residual capacity of path: %d\n", minrescapacity);

        sink = nodes[t - 1];
        while (sink.p != NULL) {

            edge = findEdge((*(sink.p)).key, sink.key);
            symedge = findEdge(sink.key, (*(sink.p)).key);

            if (edge->inOriginalGraph == 1) {
                edge->residualcapacity -= minrescapacity;
                symedge->residualcapacity += minrescapacity;

                edge->flow += minrescapacity;
                symedge->flow -= minrescapacity;
            }

            sink = *(sink.p);
        }
        maxflow += minrescapacity;
    }
    //writetofile();
    printf("\nMaximum flow of graph: %d\n", maxflow);
}

void EdmondsKarp()
{
    int s, t;
    do {
        printf("Give source:\n");
        scanf("%d", &s);
        printf("Give sink:\n");
        scanf("%d", &t);
    } while (s < 1 || s > ARRAY_SIZE || nodes[s - 1].occupied == 0 || t < 1 || t > ARRAY_SIZE || nodes[t - 1].occupied == 0);

    EdmondsKarpAlgorithm(s, t, 0);
}

int bipartiteBFS(int s)
{

    int i, dequeued, rownum;
    pt head;

    struct Queue q;
    newQueue(&q);
    enqueue(&q, s);

    while (isQueueEmpty(q) == 0) {

        dequeued = dequeue(&q);
        //printf("%d\n", dequeued);
        rownum = dequeued - 1;
        head = rows[rownum];

        while (head != NULL) {
            if ((nodes[head->j - 1].color == '-')) {
                if (nodes[head->i - 1].color == 'R') {
                    nodes[head->j - 1].color = 'B';
                } else {
                    nodes[head->j - 1].color = 'R';
                }

                //printf("Enqueued: %d\n", head->j);
                enqueue(&q, head->j);
            } else if (nodes[head->j - 1].color == nodes[head->i - 1].color) {
                deleteQueue(&q);
                return 0;
            }

            head = head->r;
        }
        //printf("Visited: %d %c\n", nodes[rownum].key, nodes[rownum].color);
    }
    return 1;
}

void bipartitegraph()
{

    int firstnonemptyrow = 0;
    while (rows[firstnonemptyrow] == NULL) {
        firstnonemptyrow++;
    }

    //Initialization for BFS
    for (int i = 0; i < ARRAY_SIZE; i++) {

        if (nodes[i].occupied == 1) {

            nodes[i].color = '-';
        }
    }

    int bipartite, tempbipartite;

    nodes[firstnonemptyrow].color = 'R';
    bipartite = bipartiteBFS(firstnonemptyrow + 1);

    /*Check if BFS found and colored all nodes (if the graph is connected). 
    If the graph is not connected, run BFS to each component of the graph. */
    if (bipartite == 1) {

        for (int i = 0; i < ARRAY_SIZE; i++) {

            if (nodes[i].occupied == 1) {

                if (nodes[i].color == '-') {
                    nodes[i].color = 'R';
                    tempbipartite = bipartiteBFS(i + 1);
                    bipartite = bipartite * tempbipartite;
                    //If bipartite = 0 for a part of a graph (that part is not bipartite), then the entire graph is nonbipartite
                }
            }
        }
    }

    if (bipartite == 1) {
        printf("The graph is bipartite.\n\n");

        //All blue->red edges: edge.residualcapacity = 0,
        for (int i = 0; i < ARRAY_SIZE; i++) {
            if ((nodes[i].occupied) && (nodes[i].color == 'B')) {

                pt head = rows[i];
                while (head != NULL) {
                    head->residualcapacity = 0;
                    head->inOriginalGraph = 0;

                    head = head->r;
                }
                searchAndInsertEdge(i + 1, ARRAY_SIZE + 2, 1, 1);
                searchAndInsertEdge(ARRAY_SIZE + 2, i + 1, 0, 0);

            } else if ((nodes[i].occupied) && (nodes[i].color == 'R')) {

                searchAndInsertEdge(ARRAY_SIZE + 1, i + 1, 1, 1);
                searchAndInsertEdge(i + 1, ARRAY_SIZE + 1, 0, 0);
            }
        }

        EdmondsKarpAlgorithm(ARRAY_SIZE + 1, ARRAY_SIZE + 2, 2);

        printf("\nEdges in Maximum Bipartite Matching: \n");
        for (int i = 0; i < ARRAY_SIZE; i++) {
            pt head = rows[i];
            while (head != NULL) {
                if ((head->i < 31) && (head->j < 31) && (head->flow == 1)) {
                    printf("%d-%d\n", head->i, head->j);
                }
                head = head->r;
            }
        }

    } else {
        printf("The graph is not bipartite.\n");
    }
}
