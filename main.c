#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "main.h"
#define TOKEN_LEN 16

/**
 * main - simple shell
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: 0 on success
 */
int main(int argc __attribute__((unused)), char *argv[])
{
	char *line = NULL, **tokens;
	ssize_t nline;
	size_t len = 0;
	int status;

	/*signal(SIGINT, SIG_IGN);*/
	do {
		fflush(NULL);
		if (isatty(STDIN_FILENO))
			print("#cisfun$ ");
		nline = getline(&line, &len, stdin);
		if (nline < 0)
			break;
		line[nline - 1] = '\0';
		tokens = tokenizer(line); /* tokenize*/
		status = execute(tokens); /* execute*/
		if (status != 0)
			perror(argv[0]);
		free_all(tokens);
	} while (1);
	free(line);
	return (status);
}
/**
 * readline - reads till new line
 * @line: string to be stored
 * Return: return number of character read or -1 on EOF
 */
ssize_t readline(char **line)
{
	ssize_t nline;
	size_t len = 0;

	nline = getline(line, &len, stdin);
	if (nline >= 0)
		(*line)[nline - 1] = '\0';

	return (nline);
}
/**
 * tokenizer - splits str into tokens
 * @str: string to be tokenzed
 * Return: array of token strings
 */
char **tokenizer(char *str)
{
	char **tokens = NULL, *token;
	const char *DELIM = " \t\a\r";
	size_t position = 0, tok_size = TOKEN_LEN, i;

	tokens = malloc(tok_size * sizeof(char *));
	if (tokens == NULL)
		return (NULL);

	token = strtok(str, DELIM);
	while (token != NULL)
	{
		tokens[position++] = _strdup(token);

		/* If allocated memory isn't enough */
		if (position > tok_size)
		{
			tok_size += TOKEN_LEN;
			tokens = _realloc(tokens, position + 1, tok_size);
			if (tokens == NULL)
			{
				for (i = 0; i < position; i++)
					free(tokens[i]);
				return (NULL);
			}
		}
		token = strtok(NULL, DELIM);
	}
	tokens[position] = NULL;

	return (tokens);
}
/**
 * execute - execute a command
 * @args: array of strings
 * Return: status
 */
int execute(char **args)
{
	pid_t child_pid;
	int status;

	if (args == NULL || args[0] == NULL)
		return (0);
	if (getpath(&args[0]) != 0)
		return (1);

	child_pid = fork();
	if (child_pid < 0)
		return (1);

	if (child_pid == 0)
	{
		/*signal(SIGINT, SIG_DFL);*/
		if (execve(args[0], args, __environ) < 0)
			return (1);
	}
	else
		wait(&status);

	return (status);
}
/**
 * getpath - gets path for str
 * @str: path key
 * Return: status
 */
int getpath(char **str)
{
	int status = 1;
	char *path, *tok, *cmd;
	struct stat statbuf;

	if (stat(*str, &statbuf) == 0)
		return (0);
	/* get path */
	path = _getenv("PATH");

	/* find given string */
	tok = strtok(path, ":");
	while (tok != NULL)
	{
		/* find if the commmand exists in a path */
		cmd = _strdup(tok);
		_strcat(_strcat(cmd, "/"), *str);
		if (stat(cmd, &statbuf) == 0)
		{
			free(*str);
			*str = _strdup(cmd);
			status = 0;
			break;
		}
		free(cmd);
		tok = strtok(NULL, ":");
	}
	free(path);

	return (status);
}
