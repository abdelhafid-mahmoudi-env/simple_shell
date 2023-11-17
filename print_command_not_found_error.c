#include "main.h"

/**
 * print_command_not_found_error - Prints
 *	                                an error message for a failed command.
 * @command: Command that was submitted by the user.
 * @filename: Name of the file being run (unused).
 */
void print_command_not_found_error(char *command, char *filename)
{
	char *error_message = NULL;
	char *error = ": command not found\n";
	size_t num_chars;

	(void)filename;

	num_chars = string_length(error) + string_length(command) + 1;
	error_message = malloc(sizeof(char) * num_chars);

	if (error_message)
	{
		snprintf(error_message, num_chars, "%s%s", command, error);
		write(STDERR_FILENO, error_message, num_chars - 1);
		free(error_message);
	}
}
