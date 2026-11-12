#include "dog.h"
#include <stdio.h>
/**
 * print_dog - print every other character of a string
 * @d: pointers to the dog
 * Return: void
 */
void print_dog(struct dog *d)
{
	if (d == 0)
	{
	return;
	}
	if (d->name == NULL)
	printf("Name: (nil)");
	else
	printf("Name: %s\n", d->name);
	if (d->age == 0)
	printf("Age: (nil)");
	else
	printf("Age: %f\n", d->age);
	if (d->owner == NULL)
	printf("Owner: (nil)");
	else
	printf("Owner: %s\n", d->owner);
}
