#include <stdio.h>
#include <stdlib.h>

typedef
	struct node *pt;
	struct node{
		int key;
		pt l, r, p;
	};
	pt temp, root, x, pred;

int flag, flag1;

void InsertTreeNode(pt *x);
void PrintTreeNode(pt x);
void DeleteTreeNode(pt *x, int y);
void FindPredecessor(pt x);


void printLevelOrder(pt x)
{
    int h = height(x);
    int i;
    for (i=1; i<=h; i++){
        printGivenLevel(x, i);
          printf("\n");}
}

void printGivenLevel(pt x, int level)
{
    if (x == NULL)
        return;
    if (level == 1){
	    printf(" %d", x->key);   
		if (x->l!=NULL)
			printf("l");
		if (x->r!=NULL)
			printf("r");   
	}
    else if (level > 1){
        printGivenLevel(x->l, level-1);
        printGivenLevel(x->r, level-1);
    }
}

int height(pt x)
{
    if (x==NULL)
        return 0;
    else
    {
        int lheight = height(x->l);
        int rheight = height(x->r);
 
        if (lheight > rheight)
            return(lheight+1);
        else return(rheight+1);
    }
}

int main(){
	
	int sel, y;
	root=NULL;
	printf("\n ---Menu Selections--- \n");
	printf("--------------------------\n");
	printf("1: Insert node in tree\n");
	printf("2: Print tree elements\n");
	printf("3: Delete node\n");
	printf("4: Quit\n");
	do{	
		
		scanf("%d", &sel);
		printf("\n");
		if (sel==1){
			flag=1;			
			InsertTreeNode(&root);}
		if (sel==2){
			printLevelOrder(root);}
		if (sel==3){
			printf("Give the unique key you want to delete:\n");
			scanf("%d", &y);
			flag1=0;
			DeleteTreeNode(&root,y);
			if (flag1==1){
				printf("The node with key %d got deleted.\n", y);				
			}
			else{
				printf("The key you entered does not exist in the BST.\n");
			}
			flag1=0;}
		if (sel==4){		
			printf("\n ---Exiting---");}
		if (sel!=4){
			printf("\nGive next menu selection:\n");}	
	}while(sel!=4);	
	return 0;
}



void InsertTreeNode(pt *x){	
	int y;
	
	if (flag==1){
		printf("Give unique key (integer) for new node:\n");
		scanf("%d", &y);
		temp=(pt)malloc(sizeof(struct node));
		temp->key=y;
		flag=0;}
	if ((*x)==NULL){
		(*x)=temp;
		(*x)->p=(*x);
		(*x)->l=NULL;
		(*x)->r=NULL;}
	else{
		if((*x)->key > temp->key){
			if((*x)->l!=NULL){
				InsertTreeNode(&(*x)->l);}
			else{
				(*x)->l=temp;
				temp->p=(*x);
				temp->l=NULL;
				temp->r=NULL;}
		}
		if((*x)->key < temp->key){
			if((*x)->r!=NULL){
				InsertTreeNode(&(*x)->r);}
			else{
				(*x)->r=temp;
				temp->p=(*x);
				temp->l=NULL;
				temp->r=NULL;}
		}
	}
}
		

void PrintTreeNode(pt x){
	
	if(x==NULL){
		printf("Empty BST");}
	else{
		if(x->l!=NULL){
			PrintTreeNode(x->l);
		}
		printf("%d \n", x->key);
		printf("POINTERS:P=%d L=%d R=%d\n", x->p->key, x->l->key, x->r->key);
		if(x->r!=NULL){
			PrintTreeNode(x->r);
		}
	}	
}

void DeleteTreeNode(pt *x, int y){	

	pt aux;
	
	if(((*x)->l!=NULL)&&((*x)->key>y)){
		DeleteTreeNode(&(*x)->l, y);
	}
	if(((*x)->r!=NULL)&&((*x)->key<y)){
		DeleteTreeNode(&(*x)->r, y);
	}
	if((*x)->key==y){
		aux=(*x);
		if((aux->l==NULL)&&(aux->r==NULL)){				
			if(aux->p->key < aux->key){
				aux->p->r=NULL;}
			else{
				aux->p->l=NULL;
			}
			if(aux==root){
				root=NULL;
			}				
			free(aux);			
			flag1=1;	
		}
		else if((aux->l!=NULL)&&(aux->r==NULL)){
			if(aux==root){
				root=aux->l;
				aux->l->p=aux->l;
			}
			else if(aux->p->key < aux->key){
				aux->p->r=aux->l;
			}
			else{
				aux->p->l=aux->l;
			}
			aux->l->p=aux->p;
			free(aux);			
			flag1=1;
		}
		else if((aux->r!=NULL)&&(aux->l==NULL)){
			if(aux==root){
				root=aux->r;
				aux->r->p=aux->r;
			}
			else if(aux->p->key < aux->key){
				aux->p->r=aux->r;
				aux->r->p=aux->p;
			}
			else{
				aux->p->l=aux->r;
				aux->r->p=aux->p;
			}					
			free(aux);			
			flag1=1;
		}
		else if((aux->r!=NULL)&&(aux->l!=NULL)){
			FindPredecessor(aux->l);
			aux->key=pred->key;
			DeleteTreeNode(&pred, pred->key);
		}	
	}
}

void FindPredecessor(pt x){
	if(x->r!=NULL){
		FindPredecessor(x->r);
	}
	else{
		pred=x;
	}
}
