#include "main.h"

/**
 * split_string - splits a string into tokens at given delimiters
 * @str: string to process
 * @delim: delimiter to split at
 *
 * Return: pointer to an array of tokens
 */
char **split_string(char *str, char *delim)
{
    size_t n_delim = 0;
    char *str_dup, *tok;
    char **tokens;

    if (!str || !delim)
        return (NULL);

    str_dup = duplicate_string(str);
    if (!str_dup)
        return (NULL);

    /* count the delimiters */
    tok = _strtok(str_dup, delim);
    while (tok)
    {
        n_delim++;
        tok = _strtok(NULL, delim);
    }

    free(str_dup);

    /* allocate memory for tokens */
    tokens = malloc(sizeof(char *) * (n_delim + 1));
    if (!tokens)
        return (NULL);

    /* tokenize the original string */
    tok = _strtok(str, delim);
    n_delim = 0;
    while (tok)
    {
        tokens[n_delim++] = tok;
        tok = _strtok(NULL, delim);
    }
    tokens[n_delim] = NULL;

    return (tokens);
}
