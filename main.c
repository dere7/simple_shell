#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
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

	while (1)
	{
		/*if (isatty(STDIN_FILENO))*/
		printf("($) ");
		nline = getline(&line, &len, stdin);
		if (nline == -1)
			break;
		line[nline - 1] = '\0';
		tokens = tokenizer(line); /* tokenize*/
		status = execute(tokens); /* execute*/
		if (status != 0)
			perror(argv[0]);
		free_all(tokens);
	}
	free(line);
	return (0);
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
	if (nline != -1)
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
		tokens[position++] = strdup(token);

		/* If allocated memory isn't enough */
		if (position > tok_size)
		{
			tok_size += TOKEN_LEN;
			tokens = realloc(tokens, tok_size);
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

	child_pid = fork();
	if (child_pid == -1)
		return (1);

	if (child_pid == 0)
	{
		if (execve(args[0], args, __environ) == -1)
			return (1);
	}
	else
		wait(&status);

	return (status);
}
