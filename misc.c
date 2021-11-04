#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

/**
 * _getenv - get an environment variable
 * @name: enviroment variable key
 * Return: status
 */
char *_getenv(char *name)
{
	int i;
	char *path;

	for (i = 0; __environ[i] != NULL; i++)
	{
		if (_strstr(__environ[i], name) != NULL)
		{
			path = _strdup(__environ[i] + _strlen(name) + 1);
			break;
		}
	}

	if (__environ[i] == NULL)
		return (NULL);
	return (path);
}
