#include <stdarg.h>
#include <stdio.h>

/**
 * print_numbers - create new dog
 * @n: numbers
 * @separator: Separator between numbers
 * Return: total number (int)
 */
void print_numbers(const char *separator, const unsigned int n, ...)
{
unsigned int i;
va_list args;


va_start(args, n);

for (i = 0; i < n; i++)
{
	printf("%i", va_arg(args, int));
	if (separator != NULL && i < (n - 1))
		printf("%s", separator);
}
printf("\n");
va_end(args);

}
