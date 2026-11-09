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
 * str_concat - concatenates two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: pointer to the concatenated string, or NULL if it fails
 */
char *str_concat(char *s1, char *s2)
{
char *array;
int i, j;
if (s1 == NULL)
s1 = "";
if (s2 == NULL)
s2 = "";
array = malloc(sizeof(char) * (_strlen(s1) + _strlen(s2) + 1));
if (array == NULL)
return (NULL);
for (i = 0; s1[i] != '\0'; i++)
{
array[i] = s1[i];
}
for (j = 0; s2[j] != '\0'; j++)
{
array[i + j] = s2[j];
}
array[i + j] = '\0';
return (array);
}
