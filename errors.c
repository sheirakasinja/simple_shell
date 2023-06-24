#include "shell.h"

/**
 * _eputs - function that prints an input string.
 * @str: the string to be printed.
 *
 */

void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - function that writes the character c to stderr.
 * @c: The character to be printed.
 *
 * Return: On success 1. On error -1 and errno is set appropriately.
 */

int _eputchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 * _putfd - function that writes character c to given fd
 * @c: character to print.
 * @fd: The filedescriptor to write to.
 *
 * Return: On success 1, On error -1 and errno is set appropriately.
 */

int _putfd(char c, int fd)
{
	static int b;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || b >= WRITE_BUF_SIZE)
	{
		write(fd, buf, b);
		b = 0;
	}
	if (c != BUF_FLUSH)
		buf[b++] = c;
	return (1);
}

/**
 * _putsfd - a function prints an input string.
 * @str: string to be printed.
 * @fd: the filedescriptor to write to.
 *
 * Return: number of characters put in function.
 */

int _putsfd(char *str, int fd)
{
	int a = 0;

	if (!str)
		return (0);
	while (*str)
	{
		a += _putfd(*str++, fd);
	}
	return (a);
}
