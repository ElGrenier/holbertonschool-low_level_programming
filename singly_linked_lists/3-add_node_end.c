#include <string.h>
#include <stdlib.h>

#include "lists.h"


/**
 * _strlen - calculate the length of a string
 * @s: pointer to the string
 *
 * Return: the length of the string
 */
int _strlen(const char *s)
{
	int len = 0;

	while (s[len] != '\0')
		len++;

return (len);
}

/**
 * add_node_end - add a new node at the end
 * @head: pointer to the head
 * @str: the string to add to the new node
 *
 * Return: list_t structure of the last node
 */
list_t *add_node_end(list_t **head, const char *str)
{
	list_t *new;
	list_t *temp;

	temp = *head;
	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);
	new->str = strdup(str);
	if (new->str == NULL)
	{
		free(new);
		return (NULL);
	}
	new->len = _strlen(str);
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
	}

	return (new);
}
