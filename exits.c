#include "shell.h"

/**
 **_strncpy - replicates a string
 *@dest: the destination string to replicate to
 *@n: the amount of characters to replicate
 *@src: the source string
 *Return: the concatenated string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - links two strings
 *@src: the second string
 *@dest: the first string
 *@n: the amount of bytes to be maximally used
 *Return: the linked string
 */

char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - finds a character in a string
 *@c: the character to look for
 *@s: the string to parse
 *Return: (s) a pointer to the memory area s
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
