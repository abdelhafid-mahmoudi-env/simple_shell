#include "main.h"

/**
 * compare_strings - compares two strings
 * @str1: first string
 * @str2: second string
 *
 * Return: 0 if they are equal, 1 if not equal
 */
int compare_strings(char *str1, char *str2)
{
    while (*str1 != '\0' && *str2 != '\0')
    {
        if (*str1 != *str2)
            return (1);
        
        str1++;
        str2++;
    }

    return (*str1 != '\0' || *str2 != '\0');
}
