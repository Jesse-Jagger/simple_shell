#include "shell.h"

/**
 * _eputs - writes an input string
 * @str: the string to print
 * Return: Null
 */

void _eputs(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to writed
 * Return: On success 1, on error, -1 is returned
 * and errno is set appropriately
*/

int _eputchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to write
 * @fd: The filedescriptor to write to
 * Return: On success 1 on error, -1 is returned and
 * errno is set appropriately
*/
int _putfd(char c, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * _putsfd - prints an input string
* @fd: the filedescriptor to write to
 * @str: the string to printed
 * Return: the number of chars put
 */

int _putsfd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += _putfd(*str++, fd);
	}
	return (j);
}
