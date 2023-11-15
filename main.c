#include "shell.h"

/**
 * main - Entry point for simple shell
 * @argc: Argument count
 * @argv: Argument vector
 * @envp: Environment variables
 * Return: 0 on success
 */
int main(int argc, char *argv[], char *envp[])
{
    char **path_values, *modify_path, **input_tokens, *input;
    char delimiter[] = DELIMITER;
    size_t n_input = 0;
    ssize_t getline_status;
    shell_t shell_ptrs;

    (void)argc;
    input = NULL;
    path_values = extract_path_tokens(&modify_path);
    display_primary_prompt(0);
    shell_ptrs.modify_path = modify_path;
    shell_ptrs.path_values = path_values;
    signal(SIGINT, SIG_IGN);

    while ((getline_status = getline(&input, &n_input, stdin)) != -1)
    {
        shell_ptrs.input = input;
        input_tokens = split_string(input, delimiter);
        shell_ptrs.input_token = input_tokens;

        if (input_tokens[0])
        {
            if (has_slash_in_command(input_tokens[0]))
                execute_path_command(&shell_ptrs, argv[0]);
            else if (process_builtin_command(&shell_ptrs, argv[0]) == 1)
                execute_user_command(&shell_ptrs, argv[0], envp);
        }

        free(input_tokens);
        display_primary_prompt(1);
    }

    free(modify_path);
    free(path_values);
    free(input);
    return (errno);
}
