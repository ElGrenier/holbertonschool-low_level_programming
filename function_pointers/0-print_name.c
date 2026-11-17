#include <stdio.h>
#include "function_pointers.h"
/**
 * print_name - print_name
 * @name: the name to print
 * @f: the pointer to the function
 * Return: void
 */
void print_name(char *name, void (*f)(char *))
{
	f(name);
}
