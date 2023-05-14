#include "main.h"

/**
 * _insertatend - add node at the end of a linked list
 * @head: head node
 * Return: Always a node
 */

 void insert_at_end(g_data *info, l_node **head, const char *str, const char *sub_data)
{
	l_node *temp, *new, *prev;

	if (!str)
		return;

	new = malloc(sizeof(l_node));
	if (!new)
	{
		free(new);
		return;
	}

	
	new->data = strdup(str);
	new->sub_data = sub_data ? strdup(sub_data) : "\'\'";
	new->next = NULL;

	if (!new->data)
	{
		free(new);
		return;
	}

	temp = *head;
	if (*head == NULL)
	{
		// new->id = 0;
		*head = new;
	}
	else 
	{
		while (temp != NULL)
		{
			prev = temp;
			temp = temp->next;
		}

		temp = new;
		// temp->id += 1;
	 	prev->next = temp;
	}

	// free(new);
	// return (new);
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
