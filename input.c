#include "main.h"

/**
 * read_line - Reads a line from standard input.
 *
 * Return: A pointer to the line read, or NULL if an error occurs.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("readline");
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}
