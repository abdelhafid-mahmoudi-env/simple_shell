#include "main.h"

/**
 * Initialize token extraction
 * @str: string to tokenize
 * @save_ptr: pointer to static variable for saving state
 * Return: adjusted string pointer
 */
char *init_token(char *str, char **save_ptr)
{
    static char *last;
    if (str != NULL)
    {
        *save_ptr = str;
    }
    else
    {
        if (last == NULL || *last == '\0')
            return NULL;
        *save_ptr = last;
    }
    return *save_ptr;
}

/**
 * Check if character is a delimiter
 * @c: character to check
 * @delim: string of delimiter characters
 * Return: 1 if delimiter, 0 otherwise
 */
int is_delim(char c, const char *delim)
{
    while (*delim)
    {
        if (c == *delim++)
            return 1;
    }
    return 0;
}

/**
 * Extract next token from string
 * @str: string to tokenize
 * @delim: string of delimiter characters
 * @save_ptr: pointer to string for saving state
 * Return: extracted token or NULL
 */
char *extract_token(char *str, const char *delim, char **save_ptr)
{
    char *end, *token = str;

    while (*str && !is_delim(*str, delim))
        str++;

    if (*str)
    {
        *str = '\0';
        *save_ptr = str + 1;
    }
    else
    {
        *save_ptr = str;
    }

    return (token == str) ? NULL : token;
}

/**
 * tokenize - tokenizes a string
 * @str: string to tokenize, or NULL to continue from last token
 * @delim: string that contains the delimiters
 * Return: pointer to the next token, or NULL if there are no more tokens.
 */
char *tokenize(char *str, const char *delim)
{
    static char *save_ptr;
    str = init_token(str, &save_ptr);

    if (str == NULL)
        return NULL;

    return extract_token(str, delim, &save_ptr);
}

