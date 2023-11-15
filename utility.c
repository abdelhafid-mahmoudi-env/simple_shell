#include "main.h"

/**
 * sigint_handler - Signal handler for SIGINT
 * @sig: The signal number
 */
void sigint_handler(int sig __attribute__((unused))) {
    (void)sig;  /* To avoid unused parameter warning */
    /* Print newline to avoid cluttering the shell prompt */
    write(STDOUT_FILENO, "\n", 1);
    /* Re-display the prompt */
    write(STDOUT_FILENO, "$ ", 2);
}

/**
 * loop - Main loop of the shell
 */
void loop(void) {
    char *line;
    char **args;
    int status;

    do {
        printf("$ ");
        line = read_line();
        args = split_line(line);
        status = execute(args);

        free(line);
        free(args);
    } while (status);
}

