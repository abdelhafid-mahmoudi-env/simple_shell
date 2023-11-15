#include "main.h"

/**
  * free_shell_resources - frees elements in shell_t struct
  * @shell_ptrs: structure of malloced elements
  */
void free_shell_resources(shell_t *shell_ptrs)
{
    if (shell_ptrs)
    {
        free(shell_ptrs->path_values);
        free(shell_ptrs->input);
        free(shell_ptrs->input_token);
        free(shell_ptrs->modify_path);
    }
}

/**
  * print_command_error - prints error for failed command
  * @command: command that was submitted by user
  * @filename: name of the file being run
  */
void print_command_error(char *command, char *filename)
{
    char *error = ": command not found\n";
    size_t error_len, command_len, total_len;

    error_len = str_length(error);
    command_len = str_length(command);
    total_len = error_len + command_len;

    char error_message[total_len + 1]; // +1 for null terminator
    strcpy(error_message, command);
    strcat(error_message, error);

    write(STDERR_FILENO, error_message, total_len);

    (void)filename; // If filename is not used, this line can be removed
}
