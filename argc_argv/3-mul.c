#include <stdio.h>
/**
 * main - print the name of the file
 * @argc: number of arguments
 * @argv: list of arguments
 * Return: void
 */
int main(int argc, char *argv[])
{
if (argc != 3)
{
	printf("Error\n");
	return (1);
}
printf("%d", (atoi(argv[1]) * atoi(argv[2])));
return (0);
}
