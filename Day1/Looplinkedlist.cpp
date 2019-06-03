
#include "Looplinkedlist.h"
#include<stdio.h>
#include<stdlib.h>

int findLoop(node *head)
{
	node *slow = head, *fast = head, *temp = head;
	while (slow&&fast&&fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (fast == slow)
		{
			while (temp != slow)
			{
				temp = temp->next;
				slow = slow->next;
			}
			break;
		}
	}
	return temp->data;
}



void findIntPoint()
{
	node *head = createlist();
	node *temp = head;
	while (temp->next)
		temp = temp->next;
	temp->next = head->next->next->next;
	int data = findLoop(head);
	printf("%d is the int point\n", data);
}