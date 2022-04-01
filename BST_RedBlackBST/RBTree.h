#ifndef RBTree_h
#define RBTree_h

typedef struct RBnode *RBTree;

/* Constructor - Initializes and returns a new RBTree. Essentially, it returns a NULL pointer
pointing to the root of the tree.
Full obstruction, client doesn't have access to the internal attributes of RBTree. */
RBTree RBTree_newRBTree();

/* Recursively inserts the key ins_key in the RBTree RBt. 
Returns:
1 - the insertion was successful
0 - the insertion was not successful (ins_key was already in the tree) 
-1 - the insertion was not successful (a call to malloc failed) */
int RBTree_insert_node(RBTree* RBt, int ins_key);

/* In-Order print of the nodes in the RBTree rbt. */
void RBTree_print_inOrder(RBTree RBt);

/* Pre-Order print of the nodes in the RBTree rbt. */
void RBTree_print_preOrder(RBTree RBt);

/* Level-Order print of the nodes in the RBTree rbt. */
void RBTree_print_levelOrder(RBTree RBt);

/* Searches for the existence of the key search_key in the tree RBt 
Returns:
1 - the insertion was successful
0 - the insertion was not successful (either ins_key was already in the tree or a call to malloc failed) 
*/
int RBTree_find_key(RBTree RBt, int search_key);

/* Searches in tree RBt for node with key del_key and deletes it. 
Returns:
1 - the deletion was successful
0 - the deletion was not successful (the node with key del_key was not found) */
int RBTree_delete_node(RBTree* RBt, int del_key);

/* Deletes the entire tree */
void RBTree_delete_tree(RBTree* RBt);
#endif