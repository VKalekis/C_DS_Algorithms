#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SparseArray.h"
//#include "LinkedList.h"
//#include "queue.h"



int main(void)
{

    int sel = 1, ranbfs = 0;
    char charsel[8];

    initializeNodeList();

    do
    {
        printf("\n ------------------------Menu Selections------------------------ \n");
        printf("-------------------------------------------------------------------\n");
        printf("1: Insert edge i-j                  \t 7: Delete edge i-j \n");
        printf("2: Insert edge i-j and j-i          \t 8: Delete edge i-j and j-i\n");
        printf("3: Insert edge i-j from .txt        \t 9: Breadth-first Search\n");
        printf("4: Insert edge i-j and j-i from .txt\t 10: Find circles in graph.\n");
        printf("5: View Sparse Array                \t 11: Quit\n");
        printf("6: View Spanning Tree               \n");

        scanf("%s", &charsel);
        printf("\n");
        sel = atoi(charsel);
        if ((sel == 1) || (sel == 2))
        {
            insertSelections(sel);
        }

        if ((sel == 3) || (sel == 4))
        {
            insertFromFile(sel);
        }

        if (sel == 5)
        {
            printSparseArray(0);
        }
        if (sel == 6)
        {
            printSparseArray(1);
        }
        if ((sel == 7) || (sel == 8))
        {
            deleteSelections(sel - 7);
        }
        if (sel == 9)
        {
            ranbfs = BFS();
        }
        if (sel == 10)
        {
            findCircles(ranbfs);
        }
        if (sel == 11)
        {
            printf("\n ---Exiting---");
        }
        if (sel != 11)
        {
            printf("\nGive next menu selection:\n");
        }
    } while (sel != 11);

    return 0;
}