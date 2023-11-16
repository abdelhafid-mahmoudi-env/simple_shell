#include "main.h"

/**
 * find_executable_path - Finds the pathname associated with the specified command.
 * @path_tokens: Pointer to the array of tokenized directories in PATH.
 * @command: Input command to find.
 *
 * Return: Path to the input file or NULL if not found.
 */
char *find_executable_path(char **path_tokens, char *command)
{
    unsigned int i;
    DIR *directory;
    struct dirent *entry;
    char *result;

    entry = NULL;

    for (i = 0; path_tokens[i] != NULL; i++)
    {
        directory = opendir(path_tokens[i]);

        if (directory == NULL)
        {
            errno = EBADF;
            return (NULL);
        }

        while ((entry = readdir(directory)) != NULL)
        {
            if (string_compare(entry->d_name, command) == 0)
            {
                result = create_pathname(path_tokens[i], command);

                if (access(result, R_OK) != -1)
                    errno = EACCES;

                closedir(directory);
                return (result);
            }
        }

        closedir(directory);
    }

    errno = EBADF;
    return (NULL);
}
