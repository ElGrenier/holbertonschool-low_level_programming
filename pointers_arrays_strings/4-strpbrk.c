#include "main.h"
/**
 * _strpbrk - locate a character in a string
 * @s: pointer to the string
 * @accept: the character to locate
 * Return: pointer of first occurrence of character, NULL if not found
 */
char *_strpbrk(char *s, char *accept)
{

unsigned int i, j;
for (i = 0; s[i] != '\0'; i++)
{

for (j = 0; accept[j] != '\0'; j++)
{
if (s[i] == accept[j])
{
return (&s[i]);
}
}
}
return (0);
}
