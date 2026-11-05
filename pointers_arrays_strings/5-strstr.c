#include "main.h"
/**
 * _strpbrk - locate a character in a string
 * @s: pointer to the string
 * @accept: the character to locate
 * Return: pointer of first occurrence of character, NULL if not found
 */
char *_strstr(char *haystack, char *needle)
{

unsigned int i, j;
for (i = 0; haystack[i] != '\0'; i++)
{
for (j = 0; needle[j] != '\0'; j++)
{
if (haystack[i] == needle[j])
{
break;
}
else
j = 0;
}
if (needle[j] == '\0')
{
return (&haystack[i]);
}
return (0);
}
return (0);
}