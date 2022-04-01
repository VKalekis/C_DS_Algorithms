#include "RBTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* RBnodept is equivalent to RBTree. It is the representation of a pointer to a node RBnode of the tree in this source file. */
typedef struct RBnode* RBnodept;
/* Each node of the RBTree. Contains key, pointers to left,right child and parent of node and a character (R or B) depending on the color of the node. */
struct RBnode {
    int key;
    RBnodept l, r, p;
    char c;
};

/* Creates new node with key ins_key in the tree whose root is RBroot. A search for the existence of the key ins_key in the tree begins when the function is called.
If the ins_key does not exist, we insert it in the tree by recursively looking for its position in the tree. After we insert it in the correct position, we call insert_fixup to restore the 
properties of the Red Black tree. 
Returns:
1 - the insertion was successful
0 - the insertion was not successful (ins_key was already in the tree) 
-1 - the insertion was not successful (a call to malloc failed)  */
int insert_node(RBnodept* RBroot, RBnodept* x, int ins_key);

/* Performs left rotation on the tree with root RBroot around the node x. */
void left_rotate(RBnodept* RBroot, RBnodept* x);

/* Performs right rotation on the tree with root RBroot around the node x. */
void right_rotate(RBnodept* RBroot, RBnodept* x);

/* Restores the properties of a Red Black tree. */
void insert_fixup(RBnodept* RBroot, RBnodept* x);

/* In-Order print of the nodes in the RBTree rbt. */
void print_inOrder(RBTree RBt);

/* Pre-Order print of the nodes in the RBTree rbt. */
void print_preOrder(RBTree RBt);

/* In-Order print of the nodes in the RBTree rbt. */
void print_levelOrder(RBTree RBt);

/* Internal function. Recursively traverses the tree, finds and deletes the node with key del_key */
void delete_node(RBnodept* RBroot, RBnodept* x, int del_key);

/* Called from delete_node. Deletes node:
if it is the only node in the tree
if it is red
if it is black with 1 red child
*/
void delete_cases(RBnodept* RBroot, RBnodept* x);

/* Called from delete_cases. Deletes a black node with 0/2 children. 
The different cases are obtained from https://www.youtube.com/watch?v=CTvfzU_uNKE */
void delete_black(RBnodept* RBroot, RBnodept* x);

/* Finds and returns successor of node x */
RBnodept find_successor(RBnodept x);

/* Safely deletes a node x by fixing its parent pointers */
void safe_delete(RBnodept* x);

/* Helper functions for print_levelOrder */
int height(RBnodept x);
void print_given_level(RBnodept x, int level);

/* Finds sibling of node x */
RBnodept find_sibling(RBnodept x);

/* Returns color (R or B) of the sibling of x */
char check_sibling_color(RBnodept x);

/* --------------------------------------------------------------- */

RBTree RBTree_newRBTree()
{
    return NULL;
}

int insert_node(RBnodept* RBroot, RBnodept* x, int ins_key)
{

    if ((*x) == NULL) {
        (*x) = (RBnodept)malloc(sizeof(struct RBnode));
        (*x)->p = NULL;
        (*x)->l = NULL;
        (*x)->r = NULL;
        (*x)->c = 'B';
        (*x)->key = ins_key;

    } else {
        if ((*x)->key > ins_key) {
            if ((*x)->l != NULL) {
                return insert_node(&(*RBroot), &(*x)->l, ins_key);
            } else {
                RBnodept temp = (RBnodept)malloc(sizeof(struct RBnode));
                if (!temp) {
                    return -1;
                }
                temp->key = ins_key;
                (*x)->l = temp;
                temp->p = (*x);
                temp->l = NULL;
                temp->r = NULL;
                temp->c = 'R';
                printf("\nInserted key: %d\n", ins_key);
                insert_fixup(&(*RBroot), &temp);
                return 1;
            }
        } else if ((*x)->key < ins_key) {
            if ((*x)->r != NULL) {
                return insert_node(&(*RBroot), &(*x)->r, ins_key);
            } else {

                RBnodept temp = (RBnodept)malloc(sizeof(struct RBnode));
                if (!temp) {
                    return -1;
                }
                temp->key = ins_key;
                (*x)->r = temp;
                temp->p = (*x);
                temp->l = NULL;
                temp->r = NULL;
                temp->c = 'R';
                printf("\nInserted key: %d\n", ins_key);
                insert_fixup(&(*RBroot), &temp);
                return 1;
            }
        }
    }
}

int RBTree_insert_node(RBTree* RBt, int ins_key)
{
    if (!RBTree_find_key(*RBt, ins_key)) {
        return insert_node(&(*RBt), &(*RBt), ins_key);
    } else {
        return 0;
    }
}

void right_rotate(RBnodept* RBroot, RBnodept* x)
{
    RBnodept y = (*x)->l, temp1 = (*x)->p;

    (*x)->l = y->r;
    if (y->r != NULL)
        y->r->p = (*x);

    if ((*x) == *RBroot) {
        *RBroot = y;
    } else if ((*x) == (*x)->p->l) {
        (*x)->p->l = y;
    } else {
        (*x)->p->r = y;
    }
    y->r = (*x);
    (*x)->p = y;
    if ((*x)->p != NULL) {
        (*x)->p->p = temp1;
    } else {
        (*x)->p->p = NULL;
    }
}

void left_rotate(RBnodept* RBroot, RBnodept* x)
{
    RBnodept y = (*x)->r, temp1 = (*x)->p;

    (*x)->r = y->l;
    if (y->l != NULL) {
        y->l->p = (*x);
    }

    if ((*RBroot) == (*x)) {
        *RBroot = y;
    } else if ((*x) == (*x)->p->l) {
        (*x)->p->l = y;
    } else {
        (*x)->p->r = y;
    }

    y->l = (*x);
    (*x)->p = y;
    if ((*x)->p != NULL) {
        (*x)->p->p = temp1;
    } else {
        (*x)->p->p = NULL;
    }
}

void insert_fixup(RBnodept* RBroot, RBnodept* x)
{
    while ((*x)->p != NULL && (*x)->p->c == 'R') {

        if ((*x)->p == (*x)->p->p->l) {

            RBnodept unc = (*x)->p->p->r;
            if ((unc != NULL) && (unc->c == 'R')) {
                unc->c = 'B';
                (*x)->p->c = 'B';
                (*x)->p->p->c = 'R';
                (*x) = (*x)->p->p;
            } else {
                if ((*x) == (*x)->p->r) {
                    (*x) = (*x)->p;
                    left_rotate(&(*RBroot), &(*x));
                }
                (*x)->p->c = 'B';
                (*x)->p->p->c = 'R';
                right_rotate(&(*RBroot), &(*x)->p->p);
            }
        } else if ((*x)->p == (*x)->p->p->r) {
            RBnodept unc = (*x)->p->p->l;
            if ((unc != NULL) && (unc->c == 'R')) {
                unc->c = 'B';
                (*x)->p->c = 'B';
                (*x)->p->p->c = 'R';
                (*x) = (*x)->p->p;
            } else {
                if ((*x) == (*x)->p->l) {
                    (*x) = (*x)->p;
                    right_rotate(&(*RBroot), &(*x));
                }
                (*x)->p->c = 'B';
                (*x)->p->p->c = 'R';
                left_rotate(&(*RBroot), &(*x)->p->p);
            }
        }
    }
    (*RBroot)->c = 'B';
}

int RBTree_delete_node(RBTree* RBt, int del_key)
{
    if (RBTree_find_key(*RBt, del_key)) {
        delete_node(&(*RBt), &(*RBt), del_key);
        return 1;
    } else {
        return 0;
    }
}

void delete_node(RBnodept* RBroot, RBnodept* x, int del_key)
{
    if (((*x)->l != NULL) && ((*x)->key > del_key))
        delete_node(&(*RBroot), &(*x)->l, del_key);
    if (((*x)->r != NULL) && ((*x)->key < del_key))
        delete_node(&(*RBroot), &(*x)->r, del_key);
    if ((*x)->key == del_key) {
        if (((*x)->l != NULL) && ((*x)->r != NULL)) {
            RBnodept suc = find_successor((*x)->r);
            (*x)->key = suc->key;
            delete_cases(&(*RBroot), &suc);
        } else
            delete_cases(&(*RBroot), &(*x));
    }
}

RBnodept find_successor(RBnodept x)
{
    if (x->l != NULL)
        return find_successor(x->l);
    else
        return x;
}

void delete_cases(RBnodept* RBroot, RBnodept* x)
{

    RBnodept aux = (*x);

    if ((*x) == (*RBroot) && (*x)->l == NULL && (*x)->r == NULL) {

        free(*x);
        *RBroot = NULL;
    } else if (aux->c == 'R') {

        if ((aux->l == NULL) && (aux->r == NULL)) {
            if (aux == aux->p->l) {
                aux->p->l = NULL;
            } else
                aux->p->r = NULL;
        } else if ((aux->l != NULL) && (aux->r == NULL)) {
            if (aux == aux->p->l)
                aux->p->l = aux->l;
            else
                aux->p->r = aux->l;
            aux->l->p = aux->p;
        } else if ((aux->l == NULL) && (aux->r != NULL)) {
            if (aux == aux->p->l)
                aux->p->l = aux->r;
            else
                aux->p->r = aux->r;
            aux->r->p = aux->p;
        }
        free(aux);
    }

    else if (aux->c == 'B') {
        if ((aux->l != NULL) && (aux->r == NULL) && (aux->l->c == 'R')) {
            if (aux == aux->p->l)
                aux->p->l = aux->l;
            else {
                aux->p->r = aux->l;
            }
            aux->l->p = aux->p;
            aux->l->c = 'B';
            free(aux);
        } else if ((aux->r != NULL) && (aux->l == NULL) && (aux->r->c == 'R')) {
            if (aux == aux->p->l)
                aux->p->l = aux->r;
            else {
                aux->p->r = aux->r;
            }
            aux->r->p = aux->p;
            aux->r->c = 'B';
            free(aux);
        } else {
            delete_black(&(*RBroot), &aux);
            safe_delete(&aux);
        }
    }
}

void safe_delete(RBnodept* x)
{
    if (((*x)->l == NULL) && ((*x)->r == NULL)) {
        if ((*x) == (*x)->p->l)
            (*x)->p->l = NULL;
        else
            (*x)->p->r = NULL;
        free((*x));
    }
}

void delete_black(RBnodept* RBroot, RBnodept* x)
{

    RBnodept aux = (*x), par = (*x)->p, sib;
    sib = find_sibling(aux);

    //Case1
    if (par == NULL) {
        aux->c = 'B';
    }

    else if (par->c == 'R') {
        //Case4
        if (sib != NULL && sib->c == 'B' && ((sib->l == NULL) || (sib->l->c == 'B')) && ((sib->r == NULL) || (sib->r->c == 'B'))) {
            par->c = 'B';
            sib->c = 'R';
        } else if (sib != NULL && sib->c == 'B') {

            if (check_sibling_color(aux) == 'r') {
                //Case5
                if (sib->l != NULL && sib->l->c == 'R' && (sib->r == NULL || sib->r->c == 'B')) {
                    right_rotate(&(*RBroot), &sib);
                    sib->c = 'R';
                    sib->p->c = 'B';
                    delete_black(&(*RBroot), &aux);
                }
                //Case6
                else if (sib->r != NULL && sib->r->c == 'R') {
                    left_rotate(&(*RBroot), &par);
                    par->p->c = par->c;
                    par->c = 'B';
                    par->p->r->c = 'B';
                }
            } else if (check_sibling_color(aux) == 'l') {
                //Case5
                if (sib->r != NULL && sib->r->c == 'R' && (sib->l == NULL || sib->l->c == 'B')) {
                    left_rotate(&(*RBroot), &sib);
                    sib->c = 'R';
                    sib->p->c = 'B';
                    delete_black(&(*RBroot), &aux);
                }
                //Case6
                else if (sib->l != NULL && sib->l->c == 'R') {
                    right_rotate(&(*RBroot), &par);
                    par->p->c = par->c;
                    par->c = 'B';
                    par->p->l->c = 'B';
                }
            }
        }
    } else if (par->c == 'B') {
        //Case 3
        if (sib != NULL && sib->c == 'B' && ((sib->l == NULL) || (sib->l->c == 'B')) && ((sib->r == NULL) || (sib->r->c == 'B'))) {
            sib->c = 'R';
            delete_black(&(*RBroot), &par);
        } else if (sib != NULL && sib->c == 'B') {
            if (check_sibling_color(aux) == 'r') {
                //Case5
                if (sib->l != NULL && sib->l->c == 'R' && (sib->r == NULL || sib->r->c == 'B')) {
                    right_rotate(&(*RBroot), &sib);
                    sib->c = 'R';
                    sib->p->c = 'B';
                    delete_black(&(*RBroot), &aux);
                }
                //Case6
                else if (sib->r != NULL && sib->r->c == 'R') {
                    left_rotate(&(*RBroot), &par);
                    par->p->c = par->c;
                    par->c = 'B';
                    par->p->r->c = 'B';
                }
            } else if (check_sibling_color(aux) == 'l') {
                //Case5
                if (sib->r != NULL && sib->r->c == 'R' && (sib->l == NULL || sib->l->c == 'B')) {
                    left_rotate(&(*RBroot), &sib);
                    sib->c = 'R';
                    sib->p->c = 'B';
                    delete_black(&(*RBroot), &aux);
                }
                //Case6
                else if (sib->l != NULL && sib->l->c == 'R') {
                    right_rotate(&(*RBroot), &par);
                    par->p->c = par->c;
                    par->c = 'B';
                    par->p->l->c = 'B';
                }
            }
        }
        //Case 2
        else if (sib != NULL && sib->c == 'R' && (sib->l == NULL || sib->l->c == 'B') && (sib->l == NULL || sib->l->c == 'B')) {
            if (check_sibling_color(aux) == 'r') {
                left_rotate(&(*RBroot), &par);
                par->c = 'R';
                par->p->c = 'B';
                delete_black(&(*RBroot), &aux);
            } else if (check_sibling_color(aux) == 'l') {
                right_rotate(&(*RBroot), &par);
                par->c = 'R';
                par->p->c = 'B';
                delete_black(&(*RBroot), &aux);
            }
        }
    }
}

RBnodept find_sibling(RBnodept x)
{
    if (x->p != NULL) {
        if (x->p->l != NULL && x->p->l != x) {
            return x->p->l;
        } else if (x->p->r != NULL && x->p->r != x) {
            return x->p->r;
        }
    }
    return NULL;
}

char check_sibling_color(RBnodept x)
{
    if (x == x->p->l) {
        return 'r';
    } else {
        return 'l';
    }
}

void RBTree_delete_tree(RBTree* RBt){
    if ((*RBt)->l!=NULL) {
        RBTree_delete_tree(&(*RBt)->l);
    }
    if ((*RBt)->r!=NULL) {
        RBTree_delete_tree(&(*RBt)->r);
    }
    free((*RBt));
}

int RBTree_find_key(RBnodept x, int search_key)
{
    if (x != NULL) {
        if ((x->l != NULL) && (x->key > search_key))
            return RBTree_find_key(x->l, search_key);

        if ((x->r != NULL) && (x->key < search_key))
            return RBTree_find_key(x->r, search_key);

        if (x->key == search_key) {
            return 1;
        }
    }
    return 0;
}

void RBTree_print_inOrder(RBTree RBt)
{
    print_inOrder(RBt);
}

void RBTree_print_preOrder(RBTree RBt)
{
    print_preOrder(RBt);
}

void RBTree_print_levelOrder(RBTree RBt)
{
    print_levelOrder(RBt);
}

void print_inOrder(RBnodept x)
{

    if (x == NULL)
        printf("Empty tree");
    else {
        if (x->l != NULL)
            print_inOrder(x->l);
        printf("%d %c\n", x->key, x->c);
        if (x->r != NULL)
            print_inOrder(x->r);
    }
}

void print_preOrder(RBnodept x)
{
    if (x == NULL)
        printf("Empty tree");
    else {
        printf("%d %c\n", x->key, x->c);
        if (x->l != NULL)
            print_preOrder(x->l);
        if (x->r != NULL)
            print_preOrder(x->r);
    }
}

void print_levelOrder(RBnodept x)
{
    int h = height(x);
    int i;
    for (i = 1; i <= h; i++) {
        print_given_level(x, i);
        printf("\n");
    }
}

void print_given_level(RBnodept x, int level)
{
    if (x == NULL)
        return;
    if (level == 1) {
        printf(" %d %c ", x->key, x->c);
        if (x->l != NULL)
            printf("l");
        if (x->r != NULL)
            printf("r");
    } else if (level > 1) {
        print_given_level(x->l, level - 1);
        print_given_level(x->r, level - 1);
    }
}

int height(RBnodept x)
{
    if (x == NULL)
        return 0;
    else {
        int lheight = height(x->l);
        int rheight = height(x->r);

        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}
