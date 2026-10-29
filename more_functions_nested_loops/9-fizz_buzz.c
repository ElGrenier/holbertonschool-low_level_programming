#include <stdio.h>
/**
 * main - Do the fizz buzz
 *
 * Return: Always 1
 */
int main(void)
{
int i;
for (i = 1; i <= 100; i++)
{
if (!(i % 3) && (i % 5))
{
printf("Fizz ");
continue;
}
if (!(i % 5) && (i % 3))
{
printf("Buzz");
if (!(i == 100))
{
printf(" ");
}
continue;
}
if (!(i % 3) && !(i % 5))
{
printf("FizzBuzz ");
continue;
}
printf("%d", i);
printf(" ");
}
return (0);
}
