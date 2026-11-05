#include "main.h"
/**
 * _strstr - locate a substring in a string
 * @haystack: pointer to the string
 * @needle: the substring to locate
 * Return: pointer of first occurrence of substring, NULL if not found
 */
char *_strstr(char *haystack, char *needle)
{

unsigned int i, j;
for (i = 0; haystack[i] != '\0'; i++)
{
for (j = 0; needle[j] != '\0'; j++)
{
if (haystack[i + j] != needle[j])
{
break;
}
}
if (needle[j] == '\0')
{
return (&haystack[i]);
}
}
return (0);
}
