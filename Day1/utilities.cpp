#include<stdlib.h>
#include<stdio.h>

typedef struct node
{
	int data;
	node *next;
}node;

static node* createnode(int data)
{
	node* n = (node *)malloc(sizeof(node));
	n->data = data;
	n->next = NULL;
	return n;
}
static void display(node* head)
{
	node *temp = head;
	while (temp != NULL)
	{
		printf("%d->", temp->data);
		temp = temp->next;
	}
	printf("NULL\n");
}

static node *createlist()
{
	int ch = 0, data;
	node* head = NULL, *temp = NULL;
	printf("create a linkded list");
	do{
		printf("enter the data\n");
		scanf("%d", &data);
		node* n = createnode(data);
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
	} while (ch != 0);
	return head;

}

