#include "main.h"

/**
 * create_pathname - Takes the result from find_executable_path and creates a string
 * containing the full pathname.
 * @path: Pathname.
 * @file: File in the path.
 *
 * Return: Pointer to an allocated string containing the full pathname.
 */
char *create_pathname(char *path, char *file)
{
    size_t path_length, file_length;
    char *result;
    unsigned int j, k;

    path_length = string_length(path);
    file_length = string_length(file);

    result = malloc(sizeof(char) * (path_length + file_length + 2));

    if (result == NULL)
        return (NULL);

    for (j = 0; j < path_length; j++)
        result[j] = path[j];

    result[j++] = '/';

    for (k = 0; k < file_length; k++)
        result[j + k] = file[k];

    result[j + k] = '\0';

    return (result);
}
