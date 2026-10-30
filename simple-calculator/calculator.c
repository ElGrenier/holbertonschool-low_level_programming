#include <stdio.h>
/**
 * ask_number - ask for numbers
 *
 * Return: x
 */
int ask_number(void)
{
int x;
scanf("%d", &x);
return (x);
}

/**
 * menu_choice - Check the choice on the menu
 * @choice: Choice in the menu
 *
 * Return: Nothing
 */
void menu_choice(int choice)
{
int a, b;
if (choice > 0 && choice < 5)
{
printf("A: ");
a = ask_number();
printf("B: ");
b = ask_number();
}
switch (choice)
{
case 0:
printf("Bye!");
break;
case 1:
printf("Result %d", a + b);
break;
case 2:
printf("Result %d", a - b);
break;
case 3:
printf("Result %d", a *b);
break;
case 4:
if (b == 0)
{
printf("Error: division by zero");
}
else
{
printf("Result %d", a / b);
}
break;

default:
printf("Invalid choice");
}
}

/**
 * main - the calculator
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
menu_choice(choice);
printf("\n");
}
return (0);
}

