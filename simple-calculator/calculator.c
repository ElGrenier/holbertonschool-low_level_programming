#include <stdio.h>
/**
 * addition - do an adition
 *
 * Return: Nothing
 */
void addition(void)
{
int a, b;
printf("A: ");
scanf("%d", &a);
printf("B: ");
scanf("%d", &b);
printf("Result: ");
printf("%d", a + b);
printf("\n");
}
/**
 * main - Make the calculator work
 *
 * Return: Always 0
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
printf("Choice: ");
scanf("%d", &choice);
if (choice > 4)
{
printf("Invalid choice");
}
if (choice == 0)
{
printf("Bye!\n");
}
if (choice == 1)
addition();
}
return (0);
}
