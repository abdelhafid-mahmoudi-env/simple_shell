#include "main.h"

/**
 * tokenize_string - tokenizes a string
 * @str: string to tokenize
 * @delim: string that contains the delimiters
 * Return: pointer to the next token in the string, or NULL if no more tokens are found.
 */
char *tokenize_string(char *str, const char *delim)
{
	static char *begin, *end_str, *end;
	unsigned int i, j;
	int word_found = 0;

	if (str == NULL)
	{
		if (begin == NULL || end == NULL)
			return (NULL);
		str = end + 1;
	}
	else
		end_str = str + string_length(str);
	for (i = 0; str + i < end_str; i++)
	{
		for (j = 0; delim != NULL && delim[j] != '\0'; j++)
		{
			if (str[i] == delim[j])
			{
				if (word_found == 1)
				{
					str[i] = '\0';
					end = str + i;
					return (begin);
				}
				break;
			}
		}
		if (delim[j] == '\0' && word_found == 0)
		{
			word_found = 1;
			begin = str + i;
		}
	}
	end = NULL;
	if (word_found == 1)
		return (begin);
	return (NULL);
}

