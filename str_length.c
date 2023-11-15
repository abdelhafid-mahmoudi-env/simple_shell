#include "main.h"

/**
 * str_length - counts length of a string
 * @str: string
 *
 * Return: number of characters in the string
 */
size_t str_length(char *str)
{
    char *s = str;
    size_t num_char = 0;

    if (str == NULL)
        return (num_char);

    while (*s != '\0')
    {
        num_char++;
        s++;
    }

    return (num_char);
}
