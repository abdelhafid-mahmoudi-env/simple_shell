#include "main.h"

/**
  * main - entry point for simple shell
  * @argc: argument count
  * @argv: argument vector
  * @envp: argument environment
  * Return: 0 on success
  */
int main(int argc, char *argv[], char *envp[])
{
	char **path_values, *modify_path, **input_token, *input;
	char delimiter[] = DELIMITER;
	size_t n_input;
	ssize_t getline_stat;
	shell_t shell_ptrs;

	(void)argc;
	input = NULL;
	path_values = get_path_tokens(&modify_path);
	print_prompt(0);
	shell_ptrs.modify_path = modify_path;
	shell_ptrs.path_values = path_values;
	signal(SIGINT, SIG_IGN);
	while ((getline_stat = getline(&input, &n_input, stdin)) != -1)
	{
		shell_ptrs.input = input;
		input_token = split_string(input, delimiter);
		shell_ptrs.input_token = input_token;
		if (input_token[0] && contains_slash(input_token[0]) == 1)
			execute_command_by_path(&shell_ptrs, argv[0]);
		else if (input_token[0] && contains_slash(input_token[0]) == 0)
		{
			if (execute_builtin_command(&shell_ptrs, argv[0]) == 1)
				execute_command(&shell_ptrs, argv[0], envp);
		}
		free(input_token);
		print_prompt(1);
	}
	free(modify_path);
	free(path_values);
	free(input);
	return (errno);
}
