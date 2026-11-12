#ifndef MAIN_H
#define MAIN_H


/**
 * struct dog - Represents a dog
 * @name: name of the dog
 * @age: age of the dog
 * @owner: owner of the dog
 */
typedef struct dog
{
	char *name;
	float age;
	char *owner;
} dog;



void init_dog(struct dog *d, char *name, float age, char *owner);

#endif
