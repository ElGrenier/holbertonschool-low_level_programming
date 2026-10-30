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
 * substraction - do an substraction
 *
 * Return: Nothing
 */
void substraction(void)
{
int a, b;
printf("A: ");
scanf("%d", &a);
printf("B: ");
scanf("%d", &b);
printf("Result: ");
printf("%d", a - b);
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
printf("1) Add\n2) Substract\n3) Multiply\n4) Divide\n0) Quit\n");
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
if (choice == 2)
substraction();
}
return (0);
}
