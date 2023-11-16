#include "main.h"
#include <string.h>

/**
 * string_compare - compares two strings
 * @str1: first string
 * @str2: second string
 * Return: 0 if they are equal, 1 if not equal
 */
int string_compare(char *str1, char *str2)
{
	while (*str1 == *str2) {
		if (*str1 == '\0') {
			return (0);
		}
		str1++;
		str2++;
	}
	return (1);
}
