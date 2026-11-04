#include <stdio.h>
/**
 * leet - convert a string to leet speak
 * @str: pointer to the string
 *
 * Return: pointer to the modified string
 */
char *leet(char *str)
{
char leet[] = "aAeEoOtTlL";
char leet_replace[] = "4433007711";
int i = 0, j = 0;
while (str[i] != '\0')
{
for (j = 0; leet[j] != '\0'; j++)
{
if (str[i] == leet[j])
{
str[i] = leet_replace[j];
}
}
i++;
}
return (str);
}
