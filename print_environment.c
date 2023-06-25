#include "shell.h"

/**
 * _myenv - a function that prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 0
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv -a function that gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: environment variable name
 *
 * Return: The value or NULL
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - a function to initialize a new environment variable or modify
 * an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: integer
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - a function to remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 0
 */

int _myunsetenv(info_t *info)
{
	int c;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (c = 1; c <= info->argc; c++)
		_unsetenv(info, info->argv[c]);

	return (0);
}

/**
 * populate_env_list - a function that populates the environment linked list
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 0
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t s;

	for (s = 0; environ[s]; s++)
		add_node_end(&node, environ[s], 0);
	info->env = node;
	return (0);
}
