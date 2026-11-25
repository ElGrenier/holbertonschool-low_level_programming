#ifndef MAIN_H
#define MAIN_H


int _putchar(char c);

/**
 * struct list_s- Represents a list
 * @str: a string
 * @len: length of the string
 * @next: next pointer of the list
 */
typedef struct list_s
{
	char *str;
	unsigned int len;
	struct list_s *next;
} list_t;

size_t print_list(const list_t *h);

#endif