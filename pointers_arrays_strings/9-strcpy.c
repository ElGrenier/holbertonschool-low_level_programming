#include <stdio.h>
/**
 * _strcpy - copy a string from source to destination
 * @dest: pointer to the destination array
 * @src: pointer to the source string
 *
 * Return: pointer to the destination string
 */
char *_strcpy(char *dest, char *src)
{
int i = 0;
for (i = 0; src[i] != '\0'; i++)
{
dest[i] = src[i];
}
dest[i] = '\0';
return (dest);
}