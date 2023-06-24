#include "shell.h"

/**
 * is_cmd - a function to determine if a file is an executable command.
 * @info: info struct.
 * @path: the path to the file.
 *
 * Return: 1 if true, 0 if false
 */

int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - a function that duplicates characters.
 * @pathstr: the PATH string
 * @start: start the index.
 * @stop: stop the index.
 *
 * Return: pointer to the new buffer.
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int e = 0, k = 0;

	for (k = 0, e = start; e < stop; e++)
		if (pathstr[e] != ':')
			buf[k++] = pathstr[e];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - function to find this cmd in the PATH string.
 * @info: the info struct.
 * @pathstr: PATH string.
 * @cmd: the cmd to find.
 *
 * Return: full path of cmd if found otherwise NULL.
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int m = 0;
       int curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[m] || pathstr[m] == ':')
		{
			path = dup_chars(pathstr, curr_pos, m);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[m])
				break;
			curr_pos = m;
		}
		m++;
	}
	return (NULL);
}
