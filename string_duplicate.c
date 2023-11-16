#include "main.h"
#include <stdlib.h>

/**
 * string_duplicate - Create an identical duplicate of a string.
 * @s: Pointer to the string to duplicate.
 *
 * Return: Pointer to the new memory address
 */
char *string_duplicate(char *s)
{
	size_t len = 0;
	char *dup;
	size_t i;

	if (s == NULL)
		return (NULL);
	while (s[len] != '\0')
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	for (i = 0; i <= len; i++)
		dup[i] = s[i];
	return (dup);
}

