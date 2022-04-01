#ifndef queue_h
#define queue_h

typedef struct qnode *ptq;
struct qnode
{
	int key;
	ptq n;
};


typedef struct Queue
{
	ptq front, rear;
}Queue;


/*Iniatilizes queue. If there's already a queue with N elements, it deletes all elements and initializes the new queue. 
	O(1) or O(N) if a queue with N elements exists. */
void newQueue(struct Queue *q);

//Inserts data in front of the queue. O(1)
void enqueue(struct Queue *q, int data);

//Removes and returns data from the rear of the queue. O(1)
int dequeue(struct Queue *q);

//Prints queue. O(N)
void printQueueExternal(struct Queue q);

//Returns 1 if queue is empty, 0 if it contains more than one elements. O(1)
int isQueueEmpty(struct Queue q);

// Deletes queue. O(N)
void deleteQueue(struct Queue *q);
#endif
