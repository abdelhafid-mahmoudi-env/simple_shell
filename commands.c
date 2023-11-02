#include "shell.h"

/**
 * execute_command - Execute the command.
 * @args: List of arguments.
 * Return: 1 if the shell should continue running, 0 if it should terminate.
 */
int execute_command(char **args)
{
    if (args[0] == NULL) {
        /* Empty command, continue the shell */
        return 1;
    }

    if (strcmp(args[0], "exit") == 0)
        return shell_exit(args);

    if (strcmp(args[0], "env") == 0)
        return shell_env(args);
    
    /* Check if the command exists */
    if (command_exists(args[0])) {
        return launch_process(args);
    } else {
        fprintf(stderr, "Command not found: %s\n", args[0]);
    }

    return 1;
}

/**
 * command_exists - Check if a command exists.
 * @command: The command to check.
 * Return: 1 if the command exists, 0 otherwise.
 */
int command_exists(const char *command)
{
    char full_path[4096]; /* Fixed size buffer */
    char *path_env;
    char *path_copy;
    char *path;

    if (access(command, X_OK) == 0)
    {
        return 1; /* Command exists and is executable */
    }

    path_env = getenv("PATH");
    if (path_env == NULL)
    {
        fprintf(stderr, "PATH environment variable not set.\n");
        return 0;
    }

    path_copy = strdup(path_env);
    path = strtok(path_copy, ":");
    
    while (path != NULL)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", path, command);
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return 1; /* Command exists in this directory */
        }
        path = strtok(NULL, ":");
    }

    free(path_copy);
    return 0; /* Command not found in any directory in PATH */
}

/**
 * launch_process - Launches a process and waits for it to terminate.
 * @args: Null terminated list of arguments.
 * Return: 1 to continue execution.
 */
int launch_process(char **args)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        /* Child process */
        if (execvp(args[0], args) == -1)
        {
            perror("simple_shell");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        /* Forking error */
        perror("simple_shell");
    }
    else
    {
        /* Parent process */
        wait(NULL);
    }
    return (1);
}

/**
 * shell_exit - Exit shell command.
 * @args: List of arguments.
 * Return: 0 to terminate execution.
 */
int shell_exit(char **args)
{
    (void) args;
    return (0);
}

/**
 * shell_env - Prints the environment.
 * @args: List of arguments.
 * Return: 1 to continue execution.
 */
int shell_env(char **args)
{
    extern char **environ;
    int i;

    (void) args;
    for (i = 0; environ[i]; i++)
        printf("%s\n", environ[i]);
    return (1);
}
