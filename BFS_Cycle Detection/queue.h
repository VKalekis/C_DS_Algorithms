#ifndef queue_h   
#define queue_h


/*Iniatilizes queue. If there's already a queue with N elements, it deletes all elements and initializes the new queue. 
	O(1) or O(N) if a queue with N elements exists. */
void newQueue(); 

//Inserts data in front of the queue. O(1)
void enqueue(int data); 

//Removes and returns data from the rear of the queue. O(1)
int dequeue(); 

//Prints queue. O(N)
void printQueueExternal(); 

//Returns 1 if queue is empty, 0 if it contains more than one elements. O(1)
int isQueueEmpty(); 

#endif 









