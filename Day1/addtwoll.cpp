#include<stdio.h>
#include<stdlib.h>
struct node{
	int data;
	struct node *next;
};
static void add(struct node *head1, struct node *head2, int *c)
{
	if (head1 && head2)
	{
		add(head1->next, head2->next, c);
		int temp = head1->data;
		head1->data = (head1->data + head2->data + *c) % 10;
		*c = (temp + head2->data + *c) / 10;
	}
}
static struct node * insert1(int x, struct node *head)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->data = x;
	temp->next = NULL;
	if (!head)
		head = temp;
	else
	{
		struct node *p = head;
		while (p->next)
			p = p->next;
		p->next = temp;
	}
	return head;
}

static void finsumll()
{
int x;
int n1, n2;
scanf_s("%d %d", &n1, &n2);
struct node *head1 = NULL;
struct node *head2 = NULL;
for (int i = 0; i < n1; i++)
{
scanf_s("%d", &x);
head1 = insert1(x, head1);
}
for (int i = 0; i < n2; i++)
{
scanf_s("%d", &x);
head2 = insert1(x, head2);
}
int c = 0;
if (n1 > n2)
{
for (int i = 0; i < n1 - n2; i++)
{
struct node *temp = (struct node *)malloc(sizeof(struct node));
temp->data = 0;
temp->next = head2;
head2 = temp;
}
}
else if (n2>n1)
{
for (int i = 0; i < n2 - n1; i++)
{
struct node *temp = (struct node *)malloc(sizeof(struct node));
temp->data = 0;
temp->next = head1;
head1 = temp;
}
}
add(head1, head2,&c);
while (head1)
{
printf("%d ", head1->data);
head1 = head1->next;

}
char ch;
scanf_s("%c", &ch);
getchar();
}