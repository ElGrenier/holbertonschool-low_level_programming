#include "dog.h"
/**
 * init_dog - print every other character of a string
 * @d: pointers to the dog
 * @name: name to set
 * @age: float, age of the dog
 * @owner: name of the owner to set
 *
 * Return: void
 */
void init_dog(struct dog *d, char *name, float age, char *owner)
{
	if (d == 0)
	{
	return;
	}
	d->name = name;
	d->age = age;
	d->owner = owner;
}
