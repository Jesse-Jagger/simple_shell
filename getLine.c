#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @buf: address of buffer
 * @len: address of len var
 * @info: parameter struct
 * Return: bytes read
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t i = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		i = getline(buf, &len_p, stdin);
#else
		i = _getline(info, buf, &len_p);
#endif
		if (i > 0)
		{
			if ((*buf)[i - 1] == '\n')
			{
				(*buf)[i - 1] = '\0'; /* remove trailing newline */
				i--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = i;
				info->cmd_buf = buf;
			}
		}
	}
	return (i);
}

/**
 * get_input - this function gets a line minus the newline
 * @info: parameter struct
 * Return: bytes read
 */

ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t a, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = a; /* init new iterator to current buf position */
		p = buf + a; /* get pointer for return */

		check_chain(info, buf, &j, a, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		a = j + 1; /* increment past nulled ';'' */
		if (a >= len) /* reached end of buffer? */
		{
			a = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @i: size
 * @buf: buffer
 * @info: parameter struct
 * Return: r
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @info: parameter struct
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t j, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (j == len)
		j = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + j, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + j, k - j);
	else
		_strncpy(new_p, buf + j, k - j + 1);

	s += k - j;
	j = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - this function blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
