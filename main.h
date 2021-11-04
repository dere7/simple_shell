#ifndef GUARD_SHELL
#define GUARD_SHELL

ssize_t readline(char **line);
char **tokenizer(char *str);
int execute(char **args);

/* memory utility */
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_all(char **tokens);

#endif
