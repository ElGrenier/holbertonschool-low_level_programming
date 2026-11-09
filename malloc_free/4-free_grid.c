#include <stdlib.h>
#include "main.h"
/**
 * free_grid - frees a grid of integers
 * @grid: pointer to the grid
 * @height: the height of the grid
 *
 * Return: pointer to the allocated grid, or NULL if it fails
 */
void free_grid(int **grid, int height)
{
int i;
if (grid == NULL || height <= 0)
return;
for (i = 0; i < height; i++)
{
free(grid[i]);
}
free(grid);
}
