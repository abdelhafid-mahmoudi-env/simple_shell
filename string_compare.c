#include "main.h"
#include <string.h>

/**
 * string_compare - Compare two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: 0 if the strings are equal, 1 if they are not equal.
 */
int string_compare(char *str1, char *str2)
{
	while (*str1 == *str2)
	{
		if (*str1 == '\0')
		{
			return (0);
		}
		str1++;
		str2++;
	}
	return (1);
}
