#include "main.h"
#include <string.h>

/**
 * split_string - function that take a string split them up at a delimiters and
 * add them into a array.
 * @str: string to process.
 * @delim: delimiter to split at.
 *
 * Return: pointer to pointers
 */
char **split_string(char *str, char *delim)
{
	size_t n_delim = 0;
	char *str_dup, *tok;
	char **tokens;

	if (!str || !delim)
		return (NULL);
	str_dup = string_duplicate(str);

	/* count the delimiters */
	tok = tokenize_string(str_dup, delim);
	while (tok)
	{
		n_delim++;
		tok = tokenize_string(NULL, delim);
	}

	/*free the str_dup*/
	free(str_dup);

	/* malloc for tokens based on n_delim + 1 for the Null */
	tokens = malloc(sizeof(char *) * (n_delim + 1));
	if (!tokens)
		return (NULL);

	/* tokenize str */
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

