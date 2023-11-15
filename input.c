#include "main.h"
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * read_line - Reads a line of input from stdin
 *
 * Return: The line from stdin
 */

char *read_line(void)
{
	char *line = NULL;

	ssize_t bufsize = 0;
	getline(&line, &bufsize, stdin);
	return (line);
}


