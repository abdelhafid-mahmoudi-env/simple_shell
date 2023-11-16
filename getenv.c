#include "main.h"

/**
 * _getenv - Gets the value of the environment variable.
 * @name: Variable to find.
 *
 * Return: Pointer to the value of the environment variable.
 */
char *_getenv(const char *name)
{
	unsigned int i, j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '=' && environ[i][j] == name[j] && name[j]; j++)
			;

		if (environ[i][j] == '=' && name[j] == '\0')
			return (&environ[i][++j]);
	}

	return (NULL);
}
