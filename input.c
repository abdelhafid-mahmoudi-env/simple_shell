#include "main.h"

/**
 * read_line - Reads a line from standard input.
 *
 * Return: A pointer to the line read, or NULL if an error or EOF occurs.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t linelen;

	linelen = getline(&line, &bufsize, stdin);

	/* Check for EOF (Ctrl+D) */
	if (linelen == -1)
	{
		free(line);
		/* If EOF is detected, exit the shell gracefully */
		if (feof(stdin))
		{
			printf("\n"); /* Print a new line for a clean exit */
			exit(EXIT_SUCCESS);
		}
		else
		{
			/* If an error occurs, handle it and exit */
			perror("readline");
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}
