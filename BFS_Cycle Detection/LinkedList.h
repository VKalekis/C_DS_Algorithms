#ifndef LinkedList_h   
#define LinkedList_h

typedef struct llnode *llnodept;
struct llnode
{
	int i, j;
	llnodept n, p;
};

typedef struct ll *llpt;
struct ll
{
	struct llnode *h;
	struct llnode *t;
};

 /* Initializes a new list and returns a pointer llpt pointing to a struct which contains pointers llnodept h,t to head and tail of the list. 
	Therefore, the list is represented with the pointer llpt. O(1) */
llpt newLinkedList();

//Inserts new node with datai, dataj before head of the list. O(1)
void llinserthead(llpt *list, int datai, int dataj); 

//Inserts new node with datai, dataj after the tail the list. O(1)
void llinserttail(llpt *list, int datai, int dataj);

//Prints list whose head is llnodept h. O(N)
void llprintrecursive(llnodept h); 

//Deletes list and frees the memory allocated to each node. O(N)
void lldeleteList(llpt *list); 

//Deletes node x of list. O(1)
void lldelete(llpt *list, llnodept *x); 

//Copies all elements from list src to list dst. O(N)
void llcopy(llpt *dst, llpt src);


#endif 


