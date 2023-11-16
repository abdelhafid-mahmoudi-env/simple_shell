#include "main.h"

/**
 * print_prompt - Prints the primary shell prompt.
 * @num: Number that determines which errno value should be set.
 */
void print_prompt(int num)
{
	char prompt[] = "$ ";
	size_t prompt_len;
	int original_error;

	original_error = errno;
	prompt_len = string_length(prompt);

	if (isatty(0))
		write(STDOUT_FILENO, prompt, prompt_len);

	if (num == 0)
		errno = 0;
	else
		errno = original_error;
}
