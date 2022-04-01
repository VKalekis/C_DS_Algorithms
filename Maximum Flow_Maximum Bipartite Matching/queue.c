#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int isQueueEmpty(struct Queue q)
{
	if (q.front != NULL)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void newQueue(struct Queue *q)
{

	q->front = NULL;
	q->rear = NULL;
	if (q->front != NULL)
	{
		while (q->front->n != NULL)
		{
			ptq temp = q->front;
			q->front = q->front->n;
			free(temp);
		}
		q->front = NULL;
		q->rear = NULL;
	}
}

void enqueue(struct Queue *q, int data)
{
	ptq temp = (ptq)malloc(sizeof(struct qnode));
	temp->key = data;
	temp->n = NULL;

	if (q->front == NULL)
	{
		q->front = temp;
		q->rear = temp;
	}
	else
	{
		q->rear->n = temp;
		q->rear = temp;
	}
}

int dequeue(struct Queue *q)
{

	if (q->front == NULL)
	{
		printf("Empty queue\n");
		return -100;
	}
	else
	{
		int frontkey = q->front->key;
		ptq temp = q->front;

		q->front = q->front->n;
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

void printQueueExternal(struct Queue q)
{
	printQueue(q.front);
}

void deleteQueue(struct Queue *q)
{
	ptq aux;
	if (q->front != NULL)
	{
		aux = q->front;
		q->front = q->front->n;
		free(aux);
	}
	q->front = NULL;
	q->rear = NULL;
}
