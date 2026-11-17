#include <stdlib.h>
#include <stdio.h>
#include "3-calc.h"
/**
 * main - do thing on the array
 * Return: void
 */
int main(int argc, char *argv[])
{
int a, b;
int (*operation)(int, int);

if (argc != 4)
{
	printf("Error");
	exit(98);
}
operation = get_op_func(argv[2]);
if (operation == NULL)
{
	printf("Error");
	exit(99);
}
	a = atoi(argv[1]);
b = atoi(argv[3]);
if ((operation == op_div || operation == op_mod) && b == 0)
{
	printf("Error");
	exit(100);
}
	printf("%d", operation(a, b));
}
