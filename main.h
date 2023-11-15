#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

extern char **environ;

int cmd_exit(char **args);
int cmd_env(char **args);
int cmd_cd(char **args);
int cmd_help(char **args, char **builtin_str);

char *read_line(void);
char **split_line(char *line);
int execute(char **args, char **builtin_str);
int launch(char **args);
int command_exists(char *cmd);
void loop(char **builtin_str);

void sigint_handler(int sig);
int shell_num_builtins(void);

#endif /* MAIN_H */

