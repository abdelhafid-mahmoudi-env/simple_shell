#include "main.h"

/**
 * contains_slash - Check if a string contains a slash character ('/').
 * @str: The input string to check.
 *
 * Return: 1 if a slash is found, 0 if no slash is found.
 */
int contains_slash(char *str)
{
    while (*str != '\0')
    {
        if (*str == '/')
            return 1;
        str++;
    }
    return (0);
}
