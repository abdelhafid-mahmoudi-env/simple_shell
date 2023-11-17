#include "main.h"

/**
 * print_command_not_found_error - Prints an error message for a failed command
 * @command: Command that was submitted by the user
 * @filename: Name of the file being run (in this case, the shell executable)
 */
void print_command_not_found_error(char *command, char *filename)
{
	char *error_message = NULL;
	char *error_format = "%s: 1: %s: not found\n";
	size_t num_chars;

	num_chars = string_length(error_format) + string_length(command) + 
				string_length(filename) - 4;

	error_message = malloc(sizeof(char) * num_chars);

	if (error_message)
	{
		snprintf(error_message, num_chars, error_format, filename, command);
		write(STDERR_FILENO, error_message, string_length(error_message));
		free(error_message);
	}
}
