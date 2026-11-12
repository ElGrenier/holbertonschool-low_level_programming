#include "dog.h"
#include <stdio.h>
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
 * _strcpy - copy a string from source to destination
 * @dest: pointer to the destination array
 * @src: pointer to the source string
 *
 * Return: pointer to the destination string
 */
char *_strcpy(char *dest, char *src)
{
int i = 0;
for (i = 0; src[i] != '\0'; i++)
{
dest[i] = src[i];
}
dest[i] = '\0';
return (dest);
}

/**
 * new_dog - create new dog
 * @name: pointers to the dog
 * @age: age of the dog
 * @owner: owner of the dog
 * Return: void
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *new_dog;

	new_dog = malloc(sizeof(dog_t));
	if (new_dog == NULL)
		return (NULL);
	new_dog->name = malloc((sizeof(char) * (_strlen(name) + 1)));

	if (new_dog->name == NULL)
	{
		free(new_dog);
		return (NULL);
	}
	_strcpy(new_dog->name, name);



	new_dog->age = age;
	new_dog->owner = malloc((sizeof(char) * (_strlen(owner) + 1)));

	if (new_dog->owner == NULL)
	{
		free(new_dog->name);
		free(new_dog);
		return (NULL);
	}
	_strcpy(new_dog->owner, owner);

	return (new_dog);
}
