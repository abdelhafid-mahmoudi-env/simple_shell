#include "shell.h"

/**
 * main - Entry point for the simple shell.
 * @argc: Argument count.
 * @argv: Argument vector.
 * Return: 0 on success, 1 on failure.
 */
int main(int argc, char **argv)
{
    	char *line;
    	char **args;
	int should_continue = 1;  /*Flag to control the loop*/

    	(void) argc;
    	(void) argv;

    while (should_continue)
    {
        printf("#cisfun$ ");
        line = read_line();
        args = split_line(line);
        if (args[0] != NULL)
            should_continue = execute_command(args);
        free(line);
        free(args);
    }

    return (0);
}
