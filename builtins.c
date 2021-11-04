#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "main.h"

/**
 * cd - change current working directory
 * @args: array of strings
 * Return: status
 */
int cd(char **args)
{
	int status;
	char *pwd = NULL;

	if (args[1] == NULL)
	{
		pwd = _getenv("HOME");
		status = chdir(pwd);
	}
	else if (_strcmp(args[1], "-") == 0)
	{
		pwd = _getenv("OLDPWD");
		status = chdir(pwd);
	}
	else
		status = chdir(args[1]);

	return (status);
}
/**
 * help - print help
 * @args: array of strings
 * @builtins: builtin
 * Return: status
 */
int help(char **args, builtin_t *builtins)
{
	int i;

	if (args[1] != NULL)
	{
		for (i = 0; builtins[i].name != NULL; i++)
			if (_strcmp(args[1], builtins[i].name) == 0)
			{
				printBuiltins(builtins[i]);
				break;
			}
		if (builtins[i].name == NULL)
		{
			print(args[1]);
			print(" not a builtin command\n");
			return (1);
		}
	}
	else
	{
		print("Simple Shell\nThe following are built in:\n");
		for (i = 0; builtins[i].name != NULL; i++)
			printBuiltins(builtins[i]);
		print("Use man for other commands\n");
	}
	return (0);
}
/**
 * cexit - exits
 * @args: array of strings
 * Return: status
 */
int cexit(char **args)
{
	if (args[1] == NULL)
		_exit(errno);
	else
		_exit(_atoi(args[1]));
}
/**
 * env - prints enviromental variables
 * @args: array of strings
 * Return: status
 */
int env(char **args __attribute__((unused)))
{
	int i;

	for (i = 0; __environ[i] != NULL; i++)
	{
		print(__environ[i]);
		_putchar('\n');
	}
	return (0);
}
/**
 * printBuiltins - prints builtins
 * @b: builtin
 */
void printBuiltins(builtin_t b)
{
	print(b.name);
	print("\t: ");
	print(b.desc);
	print("\n");
}
