#include <stdarg.h>

/**
 * sum_them_all - create new dog
 * @n: numbers
 * Return: total number (int)
 */
int sum_them_all(const unsigned int n, ...)
{
unsigned int i;
va_list args;
int somme;

somme = 0;

if (n == 0)
	return (0);

va_start(args, n);

for (i = 0; i< n; i++)
{
	somme += va_arg(args, int);
}
va_end(args);

return (somme);
}
