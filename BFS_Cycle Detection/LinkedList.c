#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"


llpt newLinkedList()
{

	llpt temp = (llpt)malloc(sizeof(struct ll));

	temp->h = NULL;
	temp->t = NULL;
	return temp;	
}

void llinserthead(llpt *list, int datai, int dataj)
{

	llnodept temp = (llnodept)malloc(sizeof(struct llnode));
	temp->i = datai;
	temp->j = dataj;
	temp->n = NULL;
	temp->p = NULL;
	if ((*list)->h == NULL)
	{
		//puts("I1");
		(*list)->h = temp;
		(*list)->t = temp;
	}
	else
	{
		temp->n = (*list)->h;
		(*list)->h->p = temp;
		(*list)->h = temp;
	}
}

void llinserttail(llpt *list, int datai, int dataj)
{
	
	llnodept temp = (llnodept)malloc(sizeof(struct llnode));
	temp->i = datai;
	temp->j = dataj;
	temp->n = NULL;
	temp->p = NULL;

	if ((*list)->h == NULL)
	{
		(*list)->h = temp;
		(*list)->t = temp;
	}
	else
	{		
		temp->p = (*list)->t;
		(*list)->t->n = temp;
		(*list)->t =temp;
	}
}

void llprintrecursive(llnodept h)
{
	llnodept aux = h;

	if (aux != NULL)
	{
		printf("%d-%d -> ", aux->i, aux->j);
		llprintrecursive(aux->n);
	}
}

void lldeleteList(llpt *list)
{
	llnodept aux;
	while ((*list)->h != NULL)
	{
		aux = (*list)->h;
		(*list)->h = (*list)->h->n;
		free(aux);
	}
	(*list)->h = NULL;
	(*list)->t = NULL;

}

void lldelete(llpt *list, llnodept *x)
{
	llnodept aux = (*x);
	
	if ((*x) == (*list)->h)
	{
		(*list)->h=(*list)->h->n;
		(*list)->h->p = NULL;
	}
	else
	{
		llnodept temppar = (*x)->p;

		(*x)->p->n = (*x)->n;

		if ((*x)->n != NULL)
		{
			(*x)->n->p = aux->p;
		}
		else {
			(*list)->t = (*x)->p;
		}		
		(*x) = temppar;
	}
	free(aux);
}

void llcopy(llpt *dst, llpt src)
{
	llpt temp = src;
	while (temp->h != NULL)
	{
		llinserttail(&(*dst), temp->h->i, temp->h->j);
		temp->h = temp->h->n;
	}
}