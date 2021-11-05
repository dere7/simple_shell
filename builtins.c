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
	free(pwd);
	return (status);
}
/**
 * help - print help
 * @args: array of strings
 * Return: status
 */
int help(char **args)
{
	int i;
	builtin_t builtins[] = {
			{ "cd", "change current working directory: cd [<pathname>]", &cd },
			{ "exit", "exits out of shell: exit [<status>]", &cexit},
			{ "env", "prints enviromental variables: env", &env  },
			{ "help", "print information about builtins: help [<command>]", &help}
	};
	int builtin_count = sizeof(builtins) / sizeof(builtin_t);

	if (args[1] != NULL)
	{
		for (i = 0; i < builtin_count; i++)
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
		for (i = 0; i < builtin_count; i++)
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
	int status;

	if (args[1] == NULL)
		status = errno;
	else
		status = _atoi(args[1]);

	free_all(args);
	exit(status);
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
