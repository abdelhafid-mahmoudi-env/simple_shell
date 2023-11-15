#include "main.h"

/**
 * duplicate_string - create an identical duplicate in new allocated memory
 * @s: pointer to string to duplicate
 *
 * Return: pointer to new memory address of duplicate
 */
char *duplicate_string(char *s)
{
    size_t i, len;
    char *dup;

    if (s == NULL)
        return (NULL);

    len = str_length(s);
    dup = malloc(sizeof(char) * (len + 1));

    if (!dup)
        return (NULL);

    for (i = 0; s[i] != '\0'; i++)
    {
        dup[i] = s[i];
    }
    dup[i] = '\0';

    return (dup);
}

