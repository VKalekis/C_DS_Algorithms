#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "LinkedList.h"
#include "SparseArray.h"

#define ARRAY_SIZE 30

pt aux, rows[ARRAY_SIZE] = {NULL}, cols[ARRAY_SIZE] = {NULL};

struct node nodes[ARRAY_SIZE];

// Recursively prints the row of the Sparse Array whose head is h. O(E)
void printrecursiveRow(pt h, int sel);

// Recursively prints the column of the Sparse Array whose head is h. O(E)
void printrecursiveColumn(pt h, int sel);

// Allocates memory for an edge. Returns pointer pt to struct edge with members i = data_i, j = data_j. O(1)
pt allocateedge(int data_i, int data_j);

/* Inserts edge insertion_edge at the correct position on the row whose head is rowhead. 
   The insertion method follows the double linked list method for inserting elements. O(E) */
void insertRow(pt *insertion_edge, pt *rowhead);

// Inserts edge insertion_edge at the correct position on the row whose head is colhead. O(E)
void insertColumn(pt *insertion_edge, pt *colhead);



/* Initializes the deletion of the edge with data i = data_i and j = data_j from the Sparse Array.
    It fixes the row pointers of the previous and next edge and it returns a pointer to the edge which will be deleted. O(E) */
pt deleteRow(int data_i, int data_j);

// Finalizes the deletion of the edge. Calls deletionfixColumnPointers and frees the memory which was allocated to that edge. O(E)
void deleteColumn(pt deledge, int data_i, int data_j);

// Fixes the column pointer of the edges above and below the edge we want to delete. O(1)
void deletefixColumnPointers(pt deledge);



/* If the graph is undirected and the edge i-j is in the Spanning Tree, 
    this function inserts the edge j-i in the Spanning Tree by going to the column with head h (with key = i) 
    and searching for the row with the key j. O(E) */
void goColumn(pt *h, int dataj);



// For a given node, it creates a linked list which contains the edges from that node up to the root of the graph (given by the user). O(E)
llpt findPathToRoot(struct node startingnode);


// For two lists list1, list2 it returns the list: list1 + list2 - intersection(list1, list2) O(E)
llpt unionandintersection(llpt *list1, llpt *list2);



pt allocateedge(int data_i, int data_j)
{

    pt insertion_edge = (pt)malloc(sizeof(struct edge));

    insertion_edge->i = data_i;
    insertion_edge->j = data_j;
    insertion_edge->l = NULL;
    insertion_edge->r = NULL;
    insertion_edge->u = NULL;
    insertion_edge->d = NULL;
    insertion_edge->inSpanningTree = 0;
    return insertion_edge;
}

void insertSelections(int sel)
{
    pt insertion_edge;
    int data_i, data_j;

    if (sel == 1)
    {
        printf("---Edge i-j insertion---\n");
    }
    else
    {
        printf("---Edge i-j and j-i insertion (Symmetric)---\n");
    }

    do
    {
        printf("Give i (1 - %d):\n", ARRAY_SIZE);
        scanf("%d", &data_i);
        printf("Give j (1 - %d):\n", ARRAY_SIZE);
        scanf("%d", &data_j);
    } while (data_i < 1 || data_i > ARRAY_SIZE || data_j < 1 || data_j > ARRAY_SIZE);

    if (sel == 1)
    {
        searchAndInsertEdge(data_i, data_j);
    }
    else if (sel == 2)
    {
        searchAndInsertEdge(data_i, data_j);
        if (data_i != data_j)
        {

            searchAndInsertEdge(data_j, data_i);
        }
    }
}

void insertRow(pt *insertion_edge, pt *rowhead)
{

    if (((*rowhead) != NULL) && ((*insertion_edge)->j > (*rowhead)->j) && ((*rowhead)->r != NULL) && ((*insertion_edge)->j > (*rowhead)->r->j))
    {
        //puts("----Row1----");
        insertRow(&(*insertion_edge), &((*rowhead)->r));
    }
    else
    {
        if (((*rowhead) != NULL) && ((*insertion_edge)->j < (*rowhead)->j))
        {
            //puts("----Row2----");
            (*insertion_edge)->r = (*rowhead);
            (*rowhead) = (*insertion_edge);
            (*rowhead)->r->l = (*rowhead);
        }
        else if (((*rowhead) != NULL) && (((*rowhead)->r == NULL) || ((*rowhead)->r->j > (*insertion_edge)->j)))
        {
            //puts("----Row3----");
            (*insertion_edge)->r = (*rowhead)->r;
            (*rowhead)->r = (*insertion_edge);
            (*insertion_edge)->l = (*rowhead);

            if ((*insertion_edge)->r != NULL)
            {
                (*insertion_edge)->r->l = (*insertion_edge);
            }
        }
        else if ((*rowhead) == NULL)
        {
            //puts("----Row4----");
            (*rowhead) = (*insertion_edge);
        }
    }
}

void insertColumn(pt *insertion_edge, pt *colhead)
{

    if (((*colhead) != NULL) && ((*insertion_edge)->i > (*colhead)->i) && ((*colhead)->d != NULL) && ((*insertion_edge)->i > (*colhead)->d->i))
    {
        // puts("----Col1----");
        insertColumn(&(*insertion_edge), &(*colhead)->d);
    }
    else
    {
        if (((*colhead) != NULL) && ((*insertion_edge)->i < (*colhead)->i))
        {
            //puts("----Col2----");
            (*insertion_edge)->d = (*colhead);
            (*colhead) = (*insertion_edge);
            (*colhead)->d->u = (*colhead);
        }
        else if (((*colhead) != NULL) && (((*colhead)->d == NULL) || ((*colhead)->d->i > (*insertion_edge)->i)))
        {
            //puts("----Col3----");
            (*insertion_edge)->d = (*colhead)->d;
            (*colhead)->d = (*insertion_edge);
            (*insertion_edge)->u = (*colhead);

            if ((*insertion_edge)->d != NULL)
            {
                (*insertion_edge)->d->u = (*insertion_edge);
            }
        }
        else if ((*colhead) == NULL)
        {
            // puts("----Col4----");
            (*colhead) = (*insertion_edge);
        }
    }
}

int search(int data_i, int data_j)
{

    int foundit = 0;
    if (rows[data_i - 1] == NULL)
    {
        foundit = 0;
    }
    else
    {
        aux = rows[data_i - 1];
        while (aux != NULL)
        {
            if (aux->j == data_j)
            {
                foundit = 1;
            }
            aux = aux->r;
        }
    }
    return foundit;
}

void searchAndInsertEdge(int x, int y)
{   
    if (x==y) {
        printf("Cannot insert edge %d-%d in SparseArray. An edge must connect two different nodes.\n", x, y);
    }
    else if (search(x, y) == 0)
    {
        pt insertion_edge = allocateedge(x, y);

        insertRow(&insertion_edge, &rows[x - 1]);
        insertColumn(&insertion_edge, &cols[y - 1]);
        printf("Inserted edge %d-%d. \n", x, y);
        nodes[x - 1].occupied = 1;
        nodes[y - 1].occupied = 1;
    }
    else
    {
        printf("Edge %d-%d already in SparseArray.\n", x, y);
    }
}

void printNodeList()
{

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("Node: %d Occupied: %d\n", i + 1, nodes[i].occupied);
        if (nodes[i].p != NULL)
        {
            printf("\n %d---%d\n", nodes[i].key, (*(nodes[i].p)).key);
        }
    }
    puts("");
}

void printSparseArray(int sel)
{
    printf("By rows\n");
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("Row[%d]: ", i + 1);
        printrecursiveRow(rows[i], sel);
        printf("\n");
    }
    printf("\n By cols\n");
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("Col[%d]: ", i + 1);
        printrecursiveColumn(cols[i], sel);
        printf("\n");
    }
}

void printrecursiveRow(pt h, int sel)
{
    pt aux = h;

    if (aux != NULL)
    {
        if ((sel == 1) && (aux->inSpanningTree == 1))
        {
            printf("%d-%d ", aux->i, aux->j);
            //printrecursiveRow(aux->r, sel);
        }
        else if (sel == 0)
        {
            printf("%d-%d ", aux->i, aux->j);
        }
        printrecursiveRow(aux->r, sel);
    }
}

void printrecursiveColumn(pt h, int sel)
{

    pt aux = h;

    if (aux != NULL)
    {
        if ((sel == 1) && (aux->inSpanningTree == 1))
        {
            printf("%d-%d ", aux->i, aux->j);
            //printrecursiveRow(aux->r, sel);
        }
        else if (sel == 0)
        {
            printf("%d-%d ", aux->i, aux->j);
        }

        printrecursiveColumn(aux->d, sel);
    }
}

void deleteSelections(int sel)
{
    int data_i, data_j, flag;

    if (sel == 0)
    {
        printf("---Edge i-j delete---\n");
    }
    else
    {
        printf("---Edge i-j and j-i delete (Symmetric)---\n");
    }

    do
    {

        printf("Edge to be deleted:\nGive i (1 - %d):\n", ARRAY_SIZE);
        scanf("%d", &data_i);
        printf("Give j (1 - %d):\n", ARRAY_SIZE);
        scanf("%d", &data_j);
    } while (data_i < 1 || data_i > ARRAY_SIZE || data_j < 1 || data_j > ARRAY_SIZE);

    if (sel == 0)
    {
        deleteEdge(data_i, data_j);
    }
    else if (sel == 1)
    {
        deleteEdge(data_i, data_j);

        if (data_i != data_j)
        {
            deleteEdge(data_j, data_j);
        }
    }

    //deleteColumn(data_i, data_j);
}

void deleteEdge(int data_i, int data_j)
{
    pt deledge;
    deledge = deleteRow(data_i, data_j);
    deleteColumn(deledge, data_i, data_j);
}

void deleteColumn(pt deledge, int data_i, int data_j)
{
    if (deledge == NULL)
    {
        printf("The edge %d-%d does not exist in the SparseArray.\n", data_i, data_j);
    }
    else
    {
        deletefixColumnPointers(deledge);
        free(deledge);
        printf("The edge %d-%d got deleted.\n", data_i, data_j);
        if ((rows[data_i - 1] == NULL) && (cols[data_i - 1] == NULL))
        {
            nodes[data_i - 1].occupied = 0;
        }
        if ((rows[data_j - 1] == NULL) && (cols[data_j - 1] == NULL))
        {
            nodes[data_j - 1].occupied = 0;
        }
    }
}

pt deleteRow(int data_i, int data_j)
{
    pt aux, aux2;
    int row_num = data_i - 1;

    if (rows[row_num] == NULL)
    {

        return NULL;
    }

    if ((rows[row_num] != NULL) && (data_j != rows[row_num]->j) && (rows[row_num]->r == NULL))
    {

        return NULL;
    }

    if ((rows[row_num] != NULL) && (data_j != rows[row_num]->j) && (rows[row_num]->r != NULL))
    {
        //printf("-----Del1-----");
        aux = rows[row_num];
        while ((aux->r != NULL) && (aux->r->j != data_j))
        {
            aux = aux->r;
        }
        if (aux->r == NULL)
        {

            return NULL;
        }
        if (aux->r != NULL)
        {
            aux2 = aux->r;
            // if (aux2 == rowsTails[row_num])
            // {
            // 	rowsTails[row_num] = aux;
            // }

            if (aux->r->r != NULL)
            {
                aux->r->r->l = aux;
            }
            aux->r = aux->r->r;

            return aux2;
        }
    }

    if ((rows[row_num] != NULL) && (data_j == rows[row_num]->j))
    {
        //printf("-----Del2-----");
        aux = rows[row_num];

        if (rows[row_num]->r != NULL)
        {
            rows[row_num]->r->l = NULL;
            rows[row_num] = rows[row_num]->r;
        }
        else
        {
            rows[row_num] = NULL;
            //rowsTails[row_num] = NULL;
        }

        return aux;
    }
}

void deletefixColumnPointers(pt aux)
{
    //printf("In function");
    if ((aux->u == NULL) && (aux->d == NULL))
    {
        cols[aux->j - 1] = NULL;
    }
    else if (aux->u == NULL)
    {
        //printf("-----Del3-----");
        cols[aux->j - 1] = aux->d;
        cols[aux->j - 1]->u = NULL;
    }
    else if (aux->d == NULL)
    {
        //printf("-----Del4-----");
        aux->u->d = NULL;
    }
    else
    {
        //printf("-----Del5-----");
        aux->u->d = aux->d;
        aux->d->u = aux->u;
    }
}

void insertFromFile(int sel)
{

    FILE *fp;
    char line[8], firstline[100];

    fp = fopen("inputEdges.txt", "r");
    fgets(firstline, sizeof(firstline), fp);

    while ((fgets(line, sizeof(line), fp) != NULL) && (strcmp(line, "\n") != 0))
    {

        char stri[4], strj[4];

        strcpy(stri, strtok(line, "-"));
        strcpy(strj, strtok(NULL, ""));

        int i = strtol(stri, NULL, 10);
        int j = strtol(strj, NULL, 10);

        if ((i > 0) && (j > 0) && (i <= ARRAY_SIZE) && (j <= ARRAY_SIZE))
        {
            if (sel == 3)
            {
                searchAndInsertEdge(i, j);
            }
            else
            {
                searchAndInsertEdge(i, j);
                if (i != j)
                {
                    searchAndInsertEdge(j, i);
                }
            }
        }
    }
    fclose(fp);
}

void initializeNodeList()
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        nodes[i].occupied = 0;
        nodes[i].key = i + 1;
    }
}

int BFS()
{
    int i, dequeued, rownum, root;
    pt head;

    //printNodeList();
    do
    {
        printf("Give root to begin BFS:\n");
        scanf("%d", &root);
    } while (root < 1 || root > ARRAY_SIZE || nodes[root - 1].occupied == 0);

    //Initialization
    for (i = 0; i < ARRAY_SIZE; i++)
    {
        nodes[i].isLeaf = 0;
        if (nodes[i].occupied == 1)
        {
            if (nodes[i].key != root)
            {
                nodes[i].color = 'W';
                nodes[i].dist = -10;
                nodes[i].p = NULL;
            }
            else
            {
                nodes[i].color = 'G';
                nodes[i].dist = 0;
                nodes[i].p = NULL;
            }

            pt aux = rows[i];
            while (aux != NULL)
            {
                aux->inSpanningTree = 0;
                aux = aux->r;
            }
        }
    }

    newQueue();
    enqueue(root);

    while (isQueueEmpty() == 0)
    {

        dequeued = dequeue();
        rownum = dequeued - 1;
        head = rows[rownum];

        while (head != NULL)
        {
            if (nodes[head->j - 1].color == 'W')
            {
                nodes[head->j - 1].color = 'G';
                nodes[head->j - 1].dist = nodes[rownum].dist + 1;
                nodes[head->j - 1].p = &nodes[rownum];
                nodes[rownum].isLeaf = 0;
                nodes[head->j - 1].isLeaf = 1;
                enqueue(head->j);

                head->inSpanningTree = 1;

                goColumn(&cols[head->i - 1], head->j);
            }

            head = head->r;
        }
        printf("Visited: %d - Distance: %d\n", nodes[rownum].key, nodes[rownum].dist);
        nodes[rownum].color = 'B';
    }

    printf("\nPaths (from leaves to root):\n");
    for (i = 0; i < ARRAY_SIZE; i++)
    {

        if (nodes[i].occupied == 1)
        {
            if ((nodes[i].isLeaf == 1) && (nodes[i].key != root))
            {
                struct node leaf = nodes[i];
                while (leaf.p != NULL)
                {
                    printf("%d -> ", leaf.key);
                    leaf = *(leaf.p);
                }
                printf("%d\n", leaf.key);
            }
        }
    }

    printf("\n-----------------------\n");
    return 1;
}

void goColumn(pt *h, int dataj)
{

    if ((*h)->d != NULL && (*h)->i != dataj)
    {
        goColumn(&(*h)->d, dataj);
    }
    else if ((*h)->i == dataj)
    {
        (*h)->inSpanningTree = 1;
    }
}

void findCircles(int ranbfs)
{
    int i;
    pt head;
    llpt list1, list2, circle;
    char choice;

    if (ranbfs == 0)
    {
        BFS();
    }
    else
    {
        printf("Do you want to run new BFS? Otherwise, I will use the existing BFS. Y/y or N/n\n");
        getchar();
        choice = getchar();
        while (choice != 'Y' && choice != 'y' && choice != 'n' && choice != 'N')
        {
            while (getchar() != '\n')
            {
            }
            printf("Wrong choice. Enter Y/y or N/n.\n");
            choice = getchar();
        }
        if (choice == 'Y' || choice == 'y')
        {
            BFS();
        }
    }

    for (i = 0; i < ARRAY_SIZE; i++)
    {

        if (nodes[i].occupied == 1)
        {

            head = rows[nodes[i].key - 1];

            while (head != NULL)
            {
                if (head->inSpanningTree == 0)
                {
                    printf("Found edge: %d - %d. Do you want to find the circle that corresponds to this edge? (Y/y or N/n)\n", head->i, head->j);
                    getchar();
                    choice = getchar();
                    while (choice != 'Y' && choice != 'y' && choice != 'n' && choice != 'N')
                    {
                        while (getchar() != '\n')
                        {
                        }
                        printf("Wrong choice. Enter Y/y or N/n.\n");
                        choice = getchar();
                    }
                    if (choice == 'Y' || choice == 'y')
                    {

                        list1 = newLinkedList();
                        list2 = newLinkedList();

                        list1 = findPathToRoot(nodes[i]);

                        list2 = findPathToRoot(nodes[head->j - 1]);

                        circle = unionandintersection(&list1, &list2);

                        llinserthead(&circle, head->i, head->j);

                        puts("\n-----------------");
                        llprintrecursive(circle->h);
                        puts("\n-----------------\n");

                        lldeleteList(&list1);
                        lldeleteList(&list2);

                        lldeleteList(&circle);
                    }
                }
                head = head->r;
            }
        }
    }
}

llpt findPathToRoot(struct node startingnode)
{

    llpt list = newLinkedList();

    while (startingnode.p != NULL)
    {

        llinserttail(&list, startingnode.key, startingnode.p->key);
        startingnode = *(startingnode.p);
    }

    return list;
}

llpt unionandintersection(llpt *list1, llpt *list2)
{

    llnodept tail1 = (*list1)->t, tail2 = (*list2)->t;
    llpt templist = newLinkedList();
    int deletedflag = 0;

    templist = newLinkedList();

    while (tail1 != NULL && tail2 != NULL)
    {
        if ((tail1->i == tail2->i) && (tail1->j = tail2->j))
        {
            lldelete(&(*list1), &tail1);
            lldelete(&(*list2), &tail2);
        }
        else
        {
            break;
        }
    }

    tail1 = (*list1)->t;
    while (tail1 != NULL)
    {
        llinserttail(&templist, tail1->j, tail1->i);
        tail1 = tail1->p;
    }

    tail2 = (*list2)->t;
    while (tail2 != NULL)
    {
        llinserthead(&templist, tail2->i, tail2->j);
        tail2 = tail2->p;
    }

    return templist;
}