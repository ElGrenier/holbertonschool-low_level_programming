#include <stdlib.h>
#include "main.h"
/**
 * _strlen - calculate the length of a string
 * @s: pointer to the string
 *
 * Return: the length of the string
 */
int _strlen(char *s)
{
int len = 0;
while (s[len] != '\0')
len++;
return (len);
}
/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 *
 * Return: pointer to the duplicated string, or NULL if it fails
 */
char *_strdup(char *str)
{
unsigned int i;
char *array;

if (str == NULL)
return (NULL);

array = malloc(sizeof(char) * (_strlen(str) + 1));
if (array == NULL)
return (NULL);
for (i = 0; i < _strlen(str); i++)
{
array[i] = str[i];
}
array[i] = '\0';
return (array);
}