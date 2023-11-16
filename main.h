#ifndef MAIN_H
#define MAIN_H

/* header files */
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <signal.h>

/**
 * struct shell_env - stores address for pointer to free.
 * @path_values: pointer to path values
 * @input: pointer to buffer that getline creates.
 * @input_token: pointers for input token.
 * @modify_path: pointer to the path after it has been modified
 *
 * Description: provides a storage for all elements that are malloced.
 */
typedef struct shell_env
{
	char **path_values;
	char *input;
	char **input_token;
	char *modify_path;
} shell_t;

/**
 * struct bicmd - struct for different built in commands.
 * @cmd_name: name of the cmd
 * @cmd: function pointer to run the cmd
 *
 * Description: struct for different built in commands in our shell
 */
typedef struct bicmd
{
	char *cmd_name;
	void (*cmd)(shell_t *);
} builtin;

char *tokenize_string(char *, const char *);
ssize_t getline(char **, size_t *, FILE *);

void cancel(shell_t *);
void enviroment(shell_t *);

void free_shell_memory(shell_t *);
void print_command_not_found_error(char *, char *);

void print_prompt(int);
char *find_executable_path(char **, char *);
char *getenv(const char *);
char *create_pathname(char *, char *);
char **get_path_tokens(char **);

size_t string_length(char *);
char *string_duplicate(char *);
char **split_string(char *, char *);
int string_compare(char *, char *);

int execute_builtin_command(shell_t *, char *);
int execute_command(shell_t *, char *, char **);
int execute_command_by_path(shell_t *, char *);
int contains_slash(char *);
void child_process(shell_t *shell_ptrs, char *filename, char **envp);

extern char **environ;

#endif

