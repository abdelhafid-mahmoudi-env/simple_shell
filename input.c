#include "main.h"

/**
 * read_line - Reads a line of input from stdin
 * Return: The line from stdin
 */
char *read_line(void) {
    char *line = NULL;
    size_t bufsize = 0;  /* Changed ssize_t to size_t */

    if (getline(&line, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            /* We received an EOF */
            exit(EXIT_SUCCESS);
        } else  {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }

    return line;
}

