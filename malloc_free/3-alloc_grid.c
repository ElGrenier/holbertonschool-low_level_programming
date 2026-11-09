#include <stdlib.h>
#include "main.h"
/**
 * _strlen - calculate the length of a string
 * @s: pointer to the string
 *
 * Return: the length of the string
 */
int _strlen(char *s)
{
int len = 0;
while (s[len] != '\0')
len++;
return (len);
}
/**
 * alloc_grid - allocates a grid of integers
 * @width: the width of the grid
 * @height: the height of the grid
 *
 * Return: pointer to the allocated grid, or NULL if it fails
 */
int **alloc_grid(int width, int height)
{
int **grid;
int i, j;
if (width <= 0 || height <= 0)
return (NULL);
grid = malloc(height * sizeof(int *));
if (grid == NULL)
return (NULL);

for (i = 0; i < height; i++)
{
grid[i] = malloc(width * sizeof(int));
if (grid[i] == NULL)
{
for (j = 0; j < i; j++)
{
free(grid[j]);
}
free(grid);
return (NULL);
}
for (j = 0; j < width; j++)
{
grid[i][j] = 0;
}
}
return (grid);
}
