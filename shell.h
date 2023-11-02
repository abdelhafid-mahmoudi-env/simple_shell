#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/* Function Prototypes */
char *read_line(void);
char **split_line(char *line);
int execute_command(char **args);
int launch_process(char **args);
int shell_exit(char **args);
int shell_env(char **args);
int command_exists(const char *command);

#endif /* _SHELL_H_ */
