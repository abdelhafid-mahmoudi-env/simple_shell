#include "main.h"

/**
 * get_path_tokens - Retrieves the PATH environment variable and tokenizes it into an array.
 * @modified_path: Pointer to store the modified path string.
 *
 * Return: Array of pointers to the tokens.
 */
char **get_path_tokens(char **modified_path)
{
    char **token_ptrs;
    char *path, *delimiter;
    unsigned int i, j, num_chars;

    delimiter = ":";
    path = getenv("PATH");
    num_chars = string_length(path);

    *modified_path = malloc(sizeof(char) * (num_chars + 2));

    if (num_chars == 0)
    {
        (*modified_path)[0] = '.';
        (*modified_path)[1] = '\0';
    }
    else
    {
        for (i = 0, j = 0; path[i] != '\0'; i++)
        {
            if (i == 0 && path[i] == ':')
            {
                (*modified_path)[j++] = '.';
                (*modified_path)[j++] = path[i];
            }
            else if (i == num_chars - 1 && path[i] == ':')
            {
                (*modified_path)[j++] = path[i];
                (*modified_path)[j++] = '.';
            }
            else if (path[i] == ':' && path[i + 1] == ':')
            {
                (*modified_path)[j++] = path[i];
                (*modified_path)[j++] = '.';
            }
            else
                (*modified_path)[j++] = path[i];
        }

        for (; j < num_chars + 2; j++)
            (*modified_path)[j] = '\0';
    }

    token_ptrs = split_string(*modified_path, delimiter);
    return (token_ptrs);
}
