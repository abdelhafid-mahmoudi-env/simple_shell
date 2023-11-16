#include "main.h"

/**
 * cancel - Exit the shell with a custom exit status.
 * @ptrs: Pointer to the shell_t structure.
 */
void cancel(shell_t *ptrs)
{
	unsigned int i;
	char *exit_str;

	exit_str = ptrs->input_token[1];
	if (exit_str != NULL || ptrs == NULL)
	{
		errno = 0;
		for (i = 0; exit_str[i] != '\0'; i++)
			errno = errno * 10 + (exit_str[i] - '0');
	}
	free_shell_memory(ptrs);
	if (errno > 255)
		errno %= 256;
	exit(errno);
}
