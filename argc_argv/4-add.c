#include <stdio.h>
#include <stdlib.h>

/**
 * main - print the name of the file
 * @argc: number of arguments
 * @argv: list of arguments
 * Return: void
 */
int main(int argc, char *argv[])
{
int result, i;
for (i = 1; i < argc ;i++)
{
	if (argv[i][0] < '0' || argv[i][0] > '9')
	{
		printf("Error\n");
		return (1);
	}
	result += atoi(argv[i]);
}

printf("%d\n", result);
return (0);
}
