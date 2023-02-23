//Isaac Orais
//Term Project
//Lab session Thu 2:15pm
//Jun 4 2022

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "list.h"

#define MAXELTS 4
struct node
{
	int length;
	int count;
	int first;
	void **data;
	struct node *next;
	struct node *prev;
}typedef NODE;

struct list
{
	int count;
	NODE *head;
	NODE *tail;
}typedef LIST;

NODE *mknode(NODE*, NODE*, int);
void delnode(NODE*);

//O(1)
LIST *createList(void)//return a pointer to a new list
{
	LIST *lp;
	lp=malloc(sizeof(LIST));
	assert(lp!=NULL);
	lp->count=1;
	lp->head=mknode(NULL, NULL, MAXELTS);
	lp->tail=lp->head;

	return lp;	
}

//O(n)
void destroyList(LIST *lp)//deallocate memory associated with the list pointed to by lp
{
	NODE *cur, *next;

	assert(lp!=NULL);

	cur=lp->head;
	while(cur!=NULL)//deallocates memory from each node pointed by lp
	{
		next=cur->next;
		delnode(cur);
		cur=next;
	}

	free(lp);

}

//O(n)
int numItems(LIST *lp)//return the number of items in the list pointed to by lp
{
	NODE *np;
	int num=0;

	assert(lp!=NULL);

	np=lp->head;
	while(np!=NULL)//adds all of the items within each node
	{
		num+=np->count;
		np=np->next;
	}

	return num;
}

//O(1)
void addFirst(LIST *lp, void *item)//add item as the first item in the list pointed to by lp
{
	NODE *cur;
	NODE *new;

	assert(lp!=NULL && item!=NULL);

	cur=lp->head;
	
	if(cur->count==cur->length)//if the node is full space is allocated for a new node
	{
		new=mknode(cur, NULL, cur->length*2);
		cur->prev=new;	
		cur=new;
		cur->data[0]=item;
		lp->head=cur;
		lp->count++;

	}
	else
	{
		cur->first=(cur->first+cur->length-1)%cur->length;
		cur->data[cur->first]=item;
	}

	cur->count++;

}

//O(1)
void addLast(LIST *lp, void *item)//add item as the last item in the list pointed to by lp
{
	NODE *cur;
	NODE *new;

	assert(lp!=NULL && item!=NULL);

	cur=lp->tail;
	
	if(cur->count==cur->length)//if the node is full space is allocated for a new node
	{
		new=mknode(NULL, cur, cur->length*2);
		cur->next=new;	
		cur=new;
		cur->data[0]=item;
		lp->tail=cur;
		lp->count++;
	}	
	else
	{
		cur->data[(cur->first+cur->count)%cur->length]=item;	
	}
	
	cur->count++;
}

//O(1)
void *removeFirst(LIST *lp)//remove and return the first item in the list pointed to by lp ; the list must not be empty
{
	NODE *cur;
	void *temp;	
	
	assert(lp!=NULL);

	cur=lp->head;
	temp=cur->data[cur->first];
	cur->count--;

	if(cur->count==0 && lp->count>1)//if the node is empty and is not the last node in the list, it is deallocated
	{
		lp->head=cur->next;
		lp->head->prev=NULL;
		delnode(cur);
		lp->count--;
	}
	else
	{
		cur->first=(cur->first+1)%cur->length;	
	}

	return temp;	
}

//O(1)
void *removeLast(LIST *lp)//remove and return the last item in the list pointed to by lp ; the list must not be empty
{
	NODE *cur;
	void *temp;	
	
	assert(lp!=NULL);

	cur=lp->tail;
	temp=cur->data[cur->first+cur->count-1];
	cur->count--;

	if(cur->count==0 && lp->count>1)//if the node is empty and is not the last node in the list, it is deallocated
	{
		lp->tail=cur->prev;
		lp->tail->next=NULL;
		delnode(cur);
		lp->count--;
	}

	return temp;
}

//O(1)
void *getFirst(LIST *lp)
{
	NODE *np=lp->head;

	assert(lp!=NULL);
		
	return np->data[(np->first)%np->length];
}

//O(1)
void *getLast(LIST *lp)
{
	NODE *np=lp->tail;

	assert(lp!=NULL);

	return np->data[(np->first+np->count-1)%np->length];
}

//O(n)
void *getItem(LIST *lp, int index)//return the item at position index in the list pointed to by lp ; the index must be within range
{
	NODE *np;

	assert(lp!=NULL);
	assert(index<numItems(lp));
	
	np=lp->head;
	while(index>=np->count)//finds the node and the location in the node that corresponds to the index
	{
		index-=np->count;		
		np=np->next;	
	}
	
	return np->data[(np->first+index)%np->length];
}

//O(n)
void setItem(LIST *lp, int index, void *item)//places item in the index received as an argument pointed by the list lp
{
	NODE *np;

	assert(lp!=NULL && item!=NULL);
	assert(index<numItems(lp));
	
	np=lp->head;
	while(index>=np->count)//finds the node and the location in the node that corresponds to the index
	{
		index-=np->count;		
		np=np->next;	
	}
	
	np->data[(np->first+index)%np->length]=item;
}

//O(1)
NODE *mknode(NODE *next, NODE *prev, int len)//allocates memory for and creates the node np
{
	NODE *np=malloc(sizeof(NODE));

	assert(np!=NULL);

	np->length=len;
	np->count=0;
	np->first=0;	

	np->next=next;
	np->prev=prev;

	np->data=malloc(sizeof(void*)*np->length);	
	assert(np->data!=NULL);

	return np;
}

//O(1)
void delnode(NODE *np)//deletes the node pointed by np
{
	assert(np!=NULL);

	free(np->data);
	free(np);		
}
