#include "main.h"

/**
 * execute_command_by_path - Execute a command specified by the pathname.
 * @shell_ptrs: Pointer to the shell_t structure containing allocated memory.
 * @filename: Name of the file (unused).
 * Return: The errno value.
 */
int execute_command_by_path(shell_t *shell_ptrs, char *filename)
{
    pid_t child_pid;
    int status;
    char **input_token = shell_ptrs->input_token;

    (void)filename;

    child_pid = fork();
    if (child_pid == 0)
    {
        if (execve(input_token[0], input_token, environ) == -1)
            perror(filename);
        free_shell_t(shell_ptrs);
        _exit(errno);
    }
    else
        wait(&status);
    errno = status % 255;
    return (errno);
}
