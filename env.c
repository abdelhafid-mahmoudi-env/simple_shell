#include "main.h"

/**
 * enviroment - Display the current environment variables.
 * @ptrs: Pointer to the shell_t structure.
 */
void enviroment(shell_t *ptrs)
{
	unsigned int i, k;
	char newline = '\n';

	(void)ptrs;
	if (environ == NULL)
		return;
	for (i = 0; environ[i] != NULL; i++)
	{
		k = string_length(environ[i]);
		if (k != 0)
		{
			write(STDOUT_FILENO, environ[i], k);
			write(STDOUT_FILENO, &newline, 1);
		}
	}
	errno = 0;
}
