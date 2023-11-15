#include "main.h"

/**
 * has_slash_in_command - checks for slashes in the command
 * @str: input string
 * Return: 1 if slash is found, 0 otherwise
 */
int has_slash_in_command(char *str)
{
    while (*str)
    {
        if (*str == '/')
            return (1);
        str++;
    }
    return (0);
}

/**
 * execute_user_command - executes the command given by the user
 * @shell_ptrs: structure containing all malloced spaces
 * @filename: name of the file being run
 * @envp: environment variable
 * Return: errno value
 */
int execute_user_command(shell_t *shell_ptrs, char *filename, char **envp)
{
    pid_t child_pid;
    int status;
    char *input_org;
    char **input_token = shell_ptrs->input_token;
    char **path = shell_ptrs->path_values;

    if (input_token[0])
    {
        child_pid = fork();
        if (child_pid == 0)
        {
            input_org = _strdup(input_token[0]);
            input_token[0] = search_command_in_path(path, input_token[0]);
            if (input_token[0])
            {
                if (execve(input_token[0], input_token, envp) == -1)
                    perror(filename);
                free(input_token[0]);
            }
            else
            {
                errno = 127;
                print_command_error(input_org, filename);
            }
            free(input_org);
            _exit(errno);
        }
        else
        {
            wait(&status);
            errno = WEXITSTATUS(status);
        }
    }
    return (errno);
}

/**
 * process_builtin_command - checks if the user calls a built-in command
 * @ptrs: contains all the malloced spaces
 * @filename: name of the file
 * Return: 1 for match not found, 0 for match found
 */
int process_builtin_command(shell_t *ptrs, char *filename)
{
    size_t index;
    char **input_words = ptrs->input_token;
    built_t cmd[] = {
        {"exit", my_exit},
        {"env", print_env},
        {NULL, NULL},
    };

    if (!input_words || !input_words[0])
        return (1);

    for (index = 0; cmd[index].cmd_name; index++)
    {
        if (strcmp(input_words[0], cmd[index].cmd_name) == 0)
        {
            cmd[index].cmd(ptrs);
            return (0);
        }
    }
    return (1);
}

/**
 * execute_path_command - runs the command specified by the pathname
 * @shell_ptrs: structure containing all malloced memory
 * @filename: filename of the file
 * Return: errno value
 */
int execute_path_command(shell_t *shell_ptrs, char *filename)
{
    pid_t child_pid;
    int status;
    char **input_token = shell_ptrs->input_token;

    child_pid = fork();
    if (child_pid == 0)
    {
        if (execve(input_token[0], input_token, environ) == -1)
            perror(filename);
        _exit(errno);
    }
    else
    {
        wait(&status);
        errno = WEXITSTATUS(status);
    }
    return (errno);
}

/**
 * execute_exit - simple implementation of exit
 * @ptrs: structure containing all malloced memory
 */
void execute_exit(shell_t *ptrs)
{
    unsigned int i;
    char *exit_str;
    int exit_code = 0;

    if (ptrs == NULL)
        exit(EXIT_FAILURE);

    exit_str = ptrs->input_token[1];
    if (exit_str != NULL)
    {
        for (i = 0; exit_str[i] != '\0'; i++)
        {
            if (!isdigit(exit_str[i]))
                exit(EXIT_FAILURE);
            exit_code = exit_code * 10 + (exit_str[i] - '0');
        }
    }
    free_shell_resources(ptrs);
    exit_code = exit_code > 255 ? exit_code % 256 : exit_code;
    exit(exit_code);
}
