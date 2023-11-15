#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/**
 * execute - Executes shell built-in or launches a program
 * @args: Null-terminated array of arguments
 * Return: 1 if the shell should continue running, 0 if it should terminate
 */
int execute(char **args)
{
    if (args[0] == NULL)
        return 1;

    if (strcmp(args[0], "exit") == 0)
        return my_exit(args);

    if (strcmp(args[0], "env") == 0)
        return my_env(args);

    return launch(args);
}

/**
 * launch - Launches a program and waits for it to terminate
 * @args: Null-terminated array of arguments (including program)
 * Return: Always returns 1, to continue execution
 */
int launch(char **args)
{
    pid_t pid, wpid;
    int status;
    char *path, *path_env_copy, *token;
    char *path_env = getenv("PATH");

    pid = fork();
    if (pid == 0)
    {
        if (execve(args[0], args, environ) == -1)
        {
            path_env_copy = strdup(path_env);
            token = strtok(path_env_copy, ":");
            while (token != NULL)
            {
                path = malloc(strlen(token) + strlen(args[0]) + 2);
                strcpy(path, token);
                strcat(path, "/");
                strcat(path, args[0]);
                execve(path, args, environ);
                free(path);
                token = strtok(NULL, ":");
            }
            free(path_env_copy);
            perror(args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("lsh");
    }
    else
    {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

/**
 * my_exit - Exit command implementation
 * @args: Command arguments
 * Return: Always returns 0, to terminate execution
 */
int my_exit(char **args)
{
    return 0;
}

/**
 * my_env - Env command implementation
 * @args: Command arguments
 * Return: Always returns 1, to continue execution
 */
int my_env(char **args)
{
    for (int i = 0; environ[i] != NULL; i++)
    {
        printf("%s\n", environ[i]);
    }
    return 1;
}

