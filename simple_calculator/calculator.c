#include <stdio.h>
/**
 * main - Make the calculator work
 *
 * Return: Always 1
 */
int main(void)
{
int choice = -1;
while (choice != 0)
{
printf("Simple Calculator\n");
printf("1) Add\n");
printf("2) Substract\n");
printf("3) Multiply\n");
printf("4) Divide\n");
printf("0) Quit\n");
scanf("%d", &choice);
if (choice == 0)
{
printf("Bye!\n");
}
}
return 0;
}
