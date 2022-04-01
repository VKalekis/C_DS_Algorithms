#include "SparseArray.h"
#include "algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Βασίλης Καλέκης - 2020507

int main(void)
{

    int sel = 1;
    char charsel[8];

    initializeNodeList();

    do {
        printf("\n ------------------------Menu Selections------------------------ \n");
        printf("-------------------------------------------------------------------\n");
        printf("1: Insert edge i-j-capacity\n");
        printf("2: Insert edges i-j-capacity from inputEdgesFF.txt for Maximum Flow in Graph\n");
        printf("3: Insert edges i-j from inputEdgesBipartite.txt for Bipartite Graph\n");
        printf("4: View Sparse Array\n");
        printf("5: Delete edge i-j\n");
        printf("6: Run Edmonds-Karp algorithm\n");
        printf("7: Run Maximum Bipartite Matching\n");
        printf("8: Quit\n");
        printf("(Max number of nodes: %d)\n", ARRAY_SIZE);
        scanf("%s", &charsel);
        printf("\n");
        sel = atoi(charsel);
        if (sel == 1) {
            insertSelections(sel);
        }

        if (sel == 2) {
            insertFromFile("inputEdgesFF.txt", 0);
        }

        if (sel == 3) {
            insertFromFile("inputEdgesBipartite.txt", 1);
        }

        if (sel == 4) {
            printSparseArray(0);
        }

        if (sel == 5) {
            deleteSelections(0);
        }
        if (sel == 6) {
            EdmondsKarp();
        }
        if (sel == 7) {
            bipartitegraph();
        }
        if (sel == 8) {
            printf("\n ---Exiting---");
        }
        if (sel != 8) {
            printf("\nGive next menu selection:\n");
        }
    } while (sel != 8);

    return 0;
}