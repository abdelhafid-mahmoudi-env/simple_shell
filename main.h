#ifndef MAIN_H
#define MAIN_H

#define DELIMITER "\t\r\n\a"

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

typedef struct shell_struct
{
    char *path_values;
    char *input;
    char *input_token;
    char *modify_path;
} shell_t;

void free_shell_resources(shell_t *shell_ptrs);
void print_command_error(char *command, char *filename);

char *tokenize(char *str, const char *delim);
char *init_token(char *str, char **save_ptr);
int is_delim(char c, const char *delim);
char *extract_token(char *str, const char *delim, char **save_ptr);

size_t str_length(char *str);
char *duplicate_string(char *s);
int compare_strings(char *str1, char *str2);

void display_primary_prompt(int num);
char **extract_path_tokens(char **modify_path);
char *search_command_in_path(char **path, char *input);
char *build_full_pathname(char *path, char *file);
char *fetch_env_variable(const char *name);

int has_slash_in_command(char *str);
int execute_user_command(shell_t *shell_ptrs, char *filename, char **envp);
int process_builtin_command(shell_t *ptrs, char *filename);
int execute_path_command(shell_t *shell_ptrs, char *filename);

void execute_exit(shell_t *ptrs);
void display_environment(shell_t *ptrs);

extern char **environ;

#endif /* MAIN_H */
