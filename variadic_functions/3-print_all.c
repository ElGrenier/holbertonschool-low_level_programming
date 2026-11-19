#include <stdarg.h>
#include <stdio.h>

/**
 * print_all - prints anything
 * @format: list of types of arguments
 * Return: nothing
 */
void print_all(const char * const format, ...)
{
	const char *list = format;
	char *temp_string;
	char *sep = "";
	va_list args;

	va_start(args, format);

	while (list != NULL && *list != '\0')
	{
		switch (*list)
		{
		case 'c':
			printf("%s%c", sep, va_arg(args, int));
			sep = ", ";
			break;
		case 'i':
			printf("%s%i", sep, va_arg(args, int));
			sep = ", ";
			break;
		case 'f':
			printf("%s%f", sep, va_arg(args, double));
			sep = ", ";
			break;
		case 's':
			temp_string = va_arg(args, char *);
			if (temp_string == NULL)
				temp_string = "(nil)";
			printf("%s%s", sep, temp_string);
			sep = ", ";
			break;
		}
		list++;
	}

	printf("\n");
	va_end(args);
}
