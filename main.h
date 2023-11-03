
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

extern char *builtin_str[];
extern int (*builtin_func[]) (char **);

/* Function prototypes for built-in shell commands: */
int cmd_exit(char **args);
int cmd_env(char **args);
int cmd_cd(char **args);
int cmd_help(char **args);

/* Function prototypes for utility functions: */
char *read_line(void);
char **split_line(char *line);
int execute(char **args);
int launch(char **args);
int command_exists(char *cmd);
void loop(void);

/* Function prototypes for signal handling: */
void sigint_handler(int sig);
int shell_num_builtins();

#endif /* MAIN_H */
