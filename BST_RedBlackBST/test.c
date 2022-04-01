#include "RBTree.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{

    RBTree RBTree1, RBTree2;

    RBTree1 = RBTree_newRBTree();
    RBTree_insert_node(&RBTree1, 4);
    RBTree_insert_node(&RBTree1, 10);
    RBTree_insert_node(&RBTree1, 5);
    printf("----\n");
    RBTree_print_inOrder(RBTree1);
    printf("----\n");

    RBTree2 = RBTree_newRBTree();
    RBTree_insert_node(&RBTree2, 2);
    RBTree_insert_node(&RBTree2, 1);
    RBTree_insert_node(&RBTree2, 3);
    RBTree_insert_node(&RBTree2, 0);
    printf("----\n");
    RBTree_print_levelOrder(RBTree2);
    printf("----\n");

    RBTree_delete_node(&RBTree2, 0);
    printf("----\n");
    RBTree_print_levelOrder(RBTree2);
    printf("----\n");

    RBTree_delete_tree(&RBTree1);
    RBTree1=NULL;
    RBTree_delete_tree(&RBTree2);
    RBTree2=NULL;
    
       
}