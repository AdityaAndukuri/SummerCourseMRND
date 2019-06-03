#include "ReverseK.h"
#include<stdio.h>
#include<stdlib.h>

node *reversek(node *head, int k)
{
	node *prev = NULL, *curr = head, *forw = NULL;
	while (k--)
	{
		forw = curr->next;
		curr->next = prev;
		prev = curr;
		curr = forw;
	}
	return prev;
}

void reversekprint()
{
	node *head = createlist();
	node *newhead = NULL, *nextnode = NULL, *tail = NULL;
	int k;
	printf("enter k value\n");
	scanf("%d", &k);
	int count = 1;
	node *temp = head, *temp2 = head;

	while (temp2)
	{
		temp2 = temp2->next;
		count++;
		if (count == k && temp2)
		{
			nextnode = temp2->next;
			if (!newhead)
			{
				newhead = reversek(temp, k);
			}
			else{
				tail->next = reversek(temp, k);
				
			}
			temp->next = nextnode;
			tail = temp;
			temp = temp->next;
			temp2 = temp;
			count = 1;
			
		}
		
	}
	
	//newhead=reversek(head, k);
	display(newhead);
}