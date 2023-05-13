#include "main.h"

/**
 * _insertatend - add node at the end of a linked list
 * @head: head node
 * Return: Always a node
 */

struct node *_insertatend(struct node *head)
{
	struct node *temt, *new;

	/*
	 * new = (struct node *)malloc(sizeof(struct node));
	 * printf("Enter data:");
	 * scanf("%d", &new->data);
	 */

	temt = head;
	while (temt != NULL)
	{
		temt = temt->next;
	}
	temt->next = new;
	return (new);
}

/**
 * _insertatbegin - add node t the begining
 * @head: head node
 * Return: Always a struct
 */
struct node *_insertatbegin(struct node *head)
{
	struct node *new;

	/*
	 * new = (struct node *)malloc(sizeof(struct node));
	 * printf("Enter data:");
	 * scanf("%d", &new->data);
	 */

	new->next = head;
	head = new;
	return (head);
}
