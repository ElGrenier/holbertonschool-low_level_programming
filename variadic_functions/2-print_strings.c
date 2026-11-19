#include <stdarg.h>
#include <stdio.h>

/**
 * print_strings - create new dog
 * @n: numbers
 * @separator: Separator between numbers
 * Return: nothing
 */
void print_strings(const char *separator, const unsigned int n, ...)
{
unsigned int i;
char *temp_string;
va_list args;


va_start(args, n);

for (i = 0; i < n; i++)
{
	temp_string = va_arg(args, char*);
	if (temp_string == NULL)
		printf("(nil)");
	else
		printf("%s", temp_string);
	if (separator != NULL && i < (n - 1))
		printf("%s", separator);
}
printf("\n");
va_end(args);

}
