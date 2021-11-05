#ifndef GUARD_SHELL
#define GUARD_SHELL
#include <stddef.h>

extern char **environ;

/* builtins */
/**
 * struct builtins_s - to manage builtin functions
 * @name: name of a command
 * @desc: short description about the function
 * @func: the associated function
 *
 * Description: manages builtin functions
 */
typedef struct builtins_s
{
	char *name, *desc;
	int (*func)(char **args);
} builtin_t;
int cd(char **args);
int help(char **args);
int cexit(char **args);
int env(char **args);
builtin_t *searchbuiltins(char *built, size_t *len);

long int readline(char **line);
char **tokenizer(char *str);
int execute(char **args);

/* utility functions */
char *_getenv(char *str);
char *getpath(char **str);

void printBuiltins(builtin_t b);

/* string manipulation */
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
char *_strstr(char *haystack, char *needle);
int _strlen(char *s);
int _atoi(char *s);
char *_strcpy(char *dest, char *src);

/* memory utility */
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_all(char **tokens);

/* misc */
void print(char *s);
int _putchar(char c);

#endif
