#include <stdio.h>
/**
 * cap_string - capitalize all words of a string
 * @str: pointer to the string
 *
 * Return: pointer to the modified string
 */
char *cap_string(char *str)
{
char separators[] = " \t\n,;.!?\"(){}";
int i = 0, j = 0;
while (str[i] != '\0')
{
if (str[0] >= 'a' && str[0] <= 'z')
{
str[0] = str[0] - 32;
}
for (j = 0; separators[j] != '\0'; j++)
{
if (str[i] == separators[j])
{
if (str[i + 1] >= 'a' && str[i + 1] <= 'z')
{
str[i + 1] = str[i + 1] - 32;
}
}
}
i++;
}
return (str);
}
