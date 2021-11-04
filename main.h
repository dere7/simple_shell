#ifndef GUARD_SHELL
#define GUARD_SHELL

ssize_t readline(char **line);
char **tokenizer(char *str);
int execute(char **args);

/* string manipulation */
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
char *_strstr(char *haystack, char *needle);
int _strlen(char *s);
int _atoi(char *s);

/* memory utility */
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_all(char **tokens);


/* misc */
void print(char *s);
int _putchar(char c);
void signal_handler(int signo);

#endif
