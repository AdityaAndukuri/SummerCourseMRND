// Summercourse.cpp : Defines the entry point for the console application.
//
#include "twoColourSort.cpp"
#include "clone.cpp"
#include "addtwoll.cpp"
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<unordered_map> 

using namespace std;

/*typedef struct node{
	int data;
	node *next;
	node *rand;
}node;

int count2;

unordered_map<void*, void*> umap;

node* createnode(int data)
{
	node* n = (node *)malloc(sizeof(node));
	n->data = data;
	n->next = NULL;
	n->rand = NULL;
	return n;
}

void display(node* head)
{
	node *temp = head;
	while (temp != NULL)
	{
		printf("%d->", temp->data);
		temp = temp->next;
	}
	printf("NULL\n");
}

node *createList()
{
	int ch = 0, data;
	node* head = NULL, *temp = NULL;
	/*printf("create a linkded list");
	do{
		printf("enter the data\n");
		scanf("%d", &data);
		node* n = createNode(data);
		if (head == NULL)
		{
			head = n;
			temp = head;
		}
		else{
			temp->next = n;
			temp = temp->next;
		}
		printf("enter 1 to continue, 0 to exit\n");
		scanf("%d", &ch);
		count++;
	}while(ch!=0);

	head->next = createnode(2);
	head->next->next = createnode(3);
	head->next->next->next = createnode(4);
	head->next->next->rand = head;
	head->next->rand = head->next->next->next;
	return head;
}

node *clonelinkedlist(node *head)
{
	node *temp = head;
	node *newhead = head;
	while (temp != NULL)
	{
		newhead->next = temp->next;
		temp = temp->next;
	}
	return newhead;
}

node *inserthash(node *head, node *newhead)
{
	node *temp1 = head, *temp2 = newhead;
	while (temp1 != NULL)
	{
		umap.insert(make_pair(&temp1, &temp2));
	}
	return temp1;
}
*/
int _tmain(int argc, _TCHAR* argv[])
{
	//coloursort();
	findclone();
	getchar();
	getchar();
	return 0;
}

