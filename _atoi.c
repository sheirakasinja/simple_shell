#include "shell.h"

/**
 * interactive - returns true if shell is in interactive mode.
 * @info: struct address.
 *
 * Return: 1 if interactive mode otherwise 0.
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if the character is a delimeter.
 * @c: character to check.
 * @delim: delimeter string.
 * Return: 1 if true, 0 if false.
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character.
 * @c: character to input.
 * Return: 1 if c is alphabetic, otherwise 0.
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer.
 * @s: string to convert.
 * Return: converted number, 0 if no numbers in string.
 */

int _atoi(char *s)
{
	int a, output;
	int sign = 1, flag = 0;
	unsigned int rslt = 0;

	for (a = 0; s[a] != '\0' && flag != 2; a++)
	{
		if (s[a] == '-')
			sign *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			flag = 1;
			rslt *= 10;
			rslt += (s[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -rslt;
	else
		output = rslt;

	return (output);
}
