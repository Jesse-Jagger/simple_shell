#include "shell.h"

/**
 * _memset - loads memory with a constant byte
 * @b: the byte to fill *s with
 * @s: the pointer to the memory area
 * @n: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 * ffree - frees string of strings
 * @pp: string of strings
 */

void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - reallocates block of memory
 * @old_size: byte size of previous block
 * @ptr: pointer to previous allocated block
 * @new_size: byte size of new block
 * Return: pointer to the old block name.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
