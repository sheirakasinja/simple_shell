#include "shell.h"

/**
 **_strncpy - a function that copies a string
 *@dest: destination string to be copied into
 *@src: the source string to copy
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i, l;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		l = i;
		while (l < n)
		{
			dest[l] = '\0';
			l++;
		}
	}
	return (s);
}

/**
 **_strncat - a function that concatenates two strings
 *@dest: first string
 *@src: second string
 *@n: amount of bytes to be maximally used
 *Return: concatenated string
 */

char *_strncat(char *dest, char *src, int n)
{
	int i, l;
	char *s = dest;

	i = 0;
	l = 0;
	while (dest[i] != '\0')
		i++;
	while (src[l] != '\0' && l < n)
	{
		dest[i] = src[l];
		i++;
		l++;
	}
	if (l < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strchr - a function that locates a character in a string
 *@s: string to be passed
 *@c: character to look for
 *Return: (s) a pointer to the memory area (s)
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
