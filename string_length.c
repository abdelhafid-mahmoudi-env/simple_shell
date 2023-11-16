#include "main.h"
#include <string.h>

/**
 * string_length - Calculate the length of a string.
 * @str: The input string.
 * Return: The length of the string.
 */
size_t string_length(char *str)
{
    size_t length = 0;

    if (str == NULL)
        return 0;

    while (*str != '\0')
    {
        length++;
        str++;
    }

    return length;
}
