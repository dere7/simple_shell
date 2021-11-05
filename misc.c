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
	char *var = NULL, *envar;

	for (i = 0; environ[i] != NULL && name != NULL; i++)
	{
		envar = strdup(environ[i]);
		var = strtok(envar, "=");
		if (strcmp(var, name) == 0)
		{
			var = strdup(strtok(NULL, "="));
			free(envar);
			return (var);
		}
		free(envar);
	}
	return (NULL);
}
