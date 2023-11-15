#include "main.h"

/**
 * main - Entry point for the simple shell.
 * @argc: The argument count.
 * @argv: An array of strings containing the command-line arguments.
 *
 * Return: EXIT_SUCCESS on success, otherwise EXIT_FAILURE.
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
