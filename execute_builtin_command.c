#include "main.h"

/**
 * execute_builtin_command - Check if the user called a built-in command.
 * @ptrs: Pointer to the shell_t structure containing allocated memory.
 * @filename: Name of the file (unused).
 * Return: 1 for match not found, 0 for match found.
 */
int execute_builtin_command(shell_t *ptrs, char *filename)
{
	size_t index;
	char **input_words;
	unsigned int num_words;

	builtin cmd[] = {
		{"exit", cancel},
		{"env", enviroment},
		{NULL, NULL}
	};

	(void)filename;
	if (!ptrs || !ptrs->input_token[0])
		return (1);
	input_words = ptrs->input_token;
	num_words = 0;
	while (input_words[num_words] != NULL)
		num_words++;
	index = 0;
	while (cmd[index].cmd_name)
	{
		if (string_compare(ptrs->input_token[0], cmd[index].cmd_name) == 0)
		{
			(cmd[index].cmd)(ptrs);
			return (0);
		}
		index++;
	}

	return (1);
}
