#include "main.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * sigint_handler - Signal handler for SIGINT
 * @sig: The signal number
 */
void sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * loop - Main loop of the shell
 */
void loop(void)
{
	char *line;
	char **args;
	int status;

	signal(2, sigint_handler);

	do {
		write(STDOUT_FILENO, "$ ", 2);
		line = read_line();
		args = split_line(line);
		status = execute(args);

		free(line);
		free(args);
	} while (status);
}
