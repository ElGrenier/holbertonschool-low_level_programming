#include <stdlib.h>
#include "main.h"
/**
 * malloc_checked - allocates memory using malloc
 * @b: size of the array
 *
 * Return: pointer to the array, or NULL if it fails
 */
void *malloc_checked(unsigned int b)
{
 void *ptr;
 ptr = malloc(b);
 if (ptr == NULL)
 {
 exit(98);
 }
 return (ptr);
}
