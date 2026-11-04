#include <stdio.h>
/**
 * _strcmp - compare two strings
 * @s1: pointer to the first string
 * @s2: pointer to the second string
 *
 * Return: integer indicating the relationship between the strings
 */
int _strcmp(char *s1, char *s2)
{
int max = 0, result_s1 = 0, result_s2 = 0;
while (s1[max] != '\0')
{
result_s1 += s1[max] - '0';	
max++;

}
while (s2[max] != '\0')
{
result_s2 += s2[max] - '0';
max++;
}
return (result_s1 - result_s2);
}
