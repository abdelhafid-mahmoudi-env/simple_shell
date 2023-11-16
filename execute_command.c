#include "main.h"

/**
 * execute_command - Execute a command specified by the user.
 * @shell_ptrs: Pointer to the shell_t structure containing allocated memory.
 * @filename: Name of the file being executed.
 * @envp: Environment variables.
 * Return: The errno value.
 */
int execute_command(shell_t *shell_ptrs, char *filename, char **envp)
{
    pid_t child_pid;
    char **input_token = shell_ptrs->input_token;
    char **path = shell_ptrs->path_values;
    int status = 0;
    char *command;
    char *input_org;
    char *executable;

    if (input_token[0] == NULL)
        return status;
    child_pid = fork();
    if (child_pid == -1)
    {
        perror("fork");
        return (1);
    }
    if (child_pid == 0)
    {
        command = input_token[0];
        input_org = string_duplicate(command);
        if (input_org == NULL)
        {
            perror("string_duplicate");
            exit(1);
        }
        executable = find_executable_path(path, command);
        if (executable != NULL)
        {
            if (execve(executable, input_token, envp) == -1)
                perror(filename);
            free(executable);
        }
        else
        {
            errno = 127;
            print_command_not_found_error(input_org, filename);
        }
        free(input_org);
        free_shell_memory(shell_ptrs);
        _exit(errno);
    }
    else
    {
        wait(&status);
        errno = WEXITSTATUS(status);
    }
    return (errno);
}
