#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* Function prototypes */
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
int launch(char **args);
int my_exit(char **args);
int my_env(char **args);

extern char **environ;

#endif /* MAIN_H */

