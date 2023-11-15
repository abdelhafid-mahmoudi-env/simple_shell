#include "main.h"

/**
 * sigint_handler - Handles the SIGINT signal.
 * @sig: The signal number.
 */
void sigint_handler(int sig __attribute__((unused)))
{
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, "#cisfun$ ", 2);
}

/**
 * loop - Main loop for the shell.
 * @builtin_str: Array of built-in commands.
 */
void loop(char **builtin_str)
{
	char *line;
	char **args;
	int status;

	signal(SIGINT, sigint_handler);

	do {
		printf("#cisfun$ ");
		line = read_line();
		args = split_line(line);
		status = execute(args, builtin_str);

		free(line);
		free(args);
	} while (status);
}
