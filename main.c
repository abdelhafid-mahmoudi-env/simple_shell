#include "main.h"
#include <stdlib.h>

/**
 * main - Entry point
 * Description: Initiates the execution of the program.
 * The command line arguments are currently unused.
 * Return: Always EXIT_SUCCESS
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 */
int main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	char *builtin_str[] = {
		"cd",
	       	"help",
		"exit",
		"env"
	};

	loop(builtin_str);
	return (EXIT_SUCCESS);
}
