#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct qnode *ptq;
struct qnode
{
	int key;
	ptq n;
};
ptq front = NULL, rear = NULL;



int isQueueEmpty() {
	if (front!=NULL) {
        return 0;
    }
    else {
        return 1;
    }
}

void newQueue() {
	if (front!=NULL) {
		while(front->n!=NULL){
			ptq temp=front;
			front=front->n;
			free(temp);
		}
		front=NULL;
		rear=NULL;
	}
}

void enqueue(int data)
{
	ptq temp = (ptq)malloc(sizeof(struct qnode));
	temp->key = data;
	temp->n = NULL;

	if (front == NULL)
	{
		front = temp;
		rear = temp;
	}
	else
	{
		rear->n = temp;
		rear = temp;
	}
}

int dequeue()
{

	if (front == NULL)
	{
		printf("Empty queue\n");
		return -100;
	}
	else
	{
		int frontkey = front->key;
		ptq temp = front;

		front = front->n;
		free(temp);
		return frontkey;
	}
}

void printQueue(ptq front)
{

	ptq aux = front;

	if (aux != NULL)
	{
		printf("%d ", aux->key);
		printQueue(aux->n);
	}
}

void printQueueExternal(){
	printQueue(front);
}

