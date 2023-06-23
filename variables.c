#include "shell.h"

/**
 * is_chain - test if current character in buffer is a chain delimeter.
 * @info: parameter struct.
 * @buf: char buffer.
 * @p: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t a = *p;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == '&' && buf[a + 1] == '&')
	{
		buf[a] = 0;
		a++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[a] == ';') /* found end of this command */
	{
		buf[a] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = a;
	return (1);
}

/**
 * check_chain - checks to continue chaining based on the last status.
 * @info: parameter struct.
 * @buf: char buffer.
 * @p: address of current position in buf.
 * @i: starting position in buf.
 * @len: length of buf.
 * Return: Void.
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t a = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			a = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			a = len;
		}
	}

	*p = a;
}

/**
 * replace_alias - replace an aliases in the tokenized string.
 * @info: parameter struct.
 * Return: 1 if replaced, otherwise 0.
 */

int replace_alias(info_t *info)
{
	int b;
	list_t *node;
	char *p;

	for (b = 0; b < 10; b++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces variables in the tokenized string.
 * @info: parameter struct.
 * Return: 1 if replaced, otherwise 0.
 */

int replace_vars(info_t *info)
{
	int b = 0;
	list_t *node;

	for (b = 0; info->argv[b]; b++)
	{
		if (info->argv[b][0] != '$' || !info->argv[b][1])
			continue;

		if (!_strcmp(info->argv[b], "$?"))
		{
			replace_string(&(info->argv[b]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[b], "$$"))
		{
			replace_string(&(info->argv[b]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[b][1], '=');
		if (node)
		{
			replace_string(&(info->argv[b]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[b], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string.
 * @old: address of old string.
 * @new: new string.
 * Return: 1 if replaced, otherwise 0.
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
