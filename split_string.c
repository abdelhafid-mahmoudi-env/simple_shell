#include "main.h"
#include <string.h>

/**
 * split_string - Splits a string into tokens using a delimiter.
 * @str: The string to process.
 * @delim: The delimiter to split at.
 *
 * Return: An array of pointers to the tokens.
 */
char **split_string(char *str, char *delim)
{
	size_t n_delim = 0;
	char *str_dup, *tok;
	char **tokens;

	if (!str || !delim)
		return (NULL);

	str_dup = string_duplicate(str);
	tok = tokenize_string(str_dup, delim);

	while (tok)
	{
		n_delim++;
		tok = tokenize_string(NULL, delim);
	}

	free(str_dup);

	tokens = malloc(sizeof(char *) * (n_delim + 1));

	if (!tokens)
		return (NULL);

	tok = tokenize_string(str, delim);
	n_delim = 0;

	while (tok)
	{
		tokens[n_delim] = tok;
		tok = tokenize_string(NULL, delim);
		n_delim++;
	}

	tokens[n_delim] = NULL;
	return (tokens);
}
