#include "main.h"
/**
 * rev_string - reverse a string
 * @s: pointer to the string
 *
 * Return: void
 */
void rev_string(char *s)
{
int i = 0, max = 0;
char temp;
/* Calculate string length */
for (; s[max] != '\0'; max++)
;
/* Reverse the string */
for (i = 0; i < max / 2; i++)
{
temp = s[i];
s[i] = s[max - 1 - i];
s[max - 1 - i] = temp;
}
}
