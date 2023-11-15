#include "main.h"

/**
 * execute - Executes shell built-in or launch program
 * @args: Null-terminated array of arguments
 *
 * Return: 1 if the shell should continue running, 0 if it should terminate
 */
int execute(char **args)
{
    if (args[0] == NULL) {
        return 1; // empty command
    }
    if (strcmp(args[0], "exit") == 0) {
        return my_exit(args);
    }
    if (strcmp(args[0], "env") == 0) {
        return my_env(args);
    }
    return launch(args);
}

/**
 * launch - Launches a program and waits for it to terminate
 * @args: Null-terminated array of arguments (including program)
 *
 * Return: Always returns 1, to continue execution
 */
int launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execve(args[0], args, environ) == -1) {
            perror("lsh");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        // Error forking
        perror("lsh");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

/**
 * my_exit - Exit command implementation
 * @args: Command arguments
 *
 * Return: Always returns 0, to terminate execution
 */
int my_exit(char **args)
{
    return 0;
}

/**
 * my_env - Env command implementation
 * @args: Command arguments
 *
 * Return: Always returns 1, to continue execution
 */
int my_env(char **args)
{
    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
    return 1;
}

