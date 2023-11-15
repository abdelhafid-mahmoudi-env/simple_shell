#include "main.h"

/**
 * display_primary_prompt - prints the primary shell prompt
 * @num: number that determines which errno value should be set
 */
void display_primary_prompt(int num)
{
    const char *ps1 = "$ ";
    size_t len_ps1 = strlen(ps1);
    int original_error = errno;

    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, ps1, len_ps1);

    errno = (num == 0) ? 0 : original_error;
}

/**
 * extract_path_tokens - get the env path and tokenizes it into an array
 * @modify_path: pointer to store modified path string into
 *
 * Return: array / double pointer
 */
char **extract_path_tokens(char **modify_path)
{
    char *path, *token, *delim = ":";
    unsigned int i, j, num_char;

    path = fetch_env_variable("PATH");
    num_char = strlen(path);
    *modify_path = malloc(sizeof(char) * (num_char + 2));

    if (num_char == 0)
    {
        (*modify_path)[0] = '.';
        (*modify_path)[1] = '\0';
    }
    else
    {
        for (i = 0, j = 0; path[i] != '\0'; i++, j++)
        {
            (*modify_path)[j] = path[i];
            if (path[i] == ':' && (i == 0 || path[i + 1] == '\0' || path[i + 1] == ':'))
            {
                (*modify_path)[++j] = '.';
            }
        }
        (*modify_path)[j] = '\0';
    }

    char **token_ptr = split_string(*modify_path, delim);
    return token_ptr;
}

/**
 * search_command_in_path - finds the pathname attached to the associated command
 * @path: pointer to 2d array of tokenized directories in PATH
 * @input: input to find
 *
 * Return: Path to the input file
 */
char *search_command_in_path(char **path, char *input)
{
    DIR *directory;
    struct dirent *filename;
    char *result = NULL;

    for (size_t i = 0; path[i] != NULL; i++)
    {
        directory = opendir(path[i]);
        if (directory != NULL)
        {
            while ((filename = readdir(directory)) != NULL)
            {
                if (strcmp(filename->d_name, input) == 0)
                {
                    result = build_full_pathname(path[i], input);
                    closedir(directory);
                    return result;
                }
            }
            closedir(directory);
        }
    }
    return NULL;
}

/**
 * build_full_pathname - creates a string containing the full pathname
 * @path: pathname
 * @file: file in the path
 *
 * Return: pointer to an allocated string that contains the full pathname
 */
char *build_full_pathname(char *path, char *file)
{
    size_t path_len = strlen(path);
    size_t file_len = strlen(file);
    char *full_path = malloc(sizeof(char) * (path_len + file_len + 2));

    if (full_path != NULL)
    {
        sprintf(full_path, "%s/%s", path, file);
    }
    return full_path;
}

/**
 * fetch_env_variable - gets the value of the environment variable
 * @name: variable to find
 *
 * Return: pointer to the value of the environment variable
 */
char *fetch_env_variable(const char *name)
{
    for (int i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], name, strlen(name)) == 0 && environ[i][strlen(name)] == '=')
        {
            return environ[i] + strlen(name) + 1;
        }
    }
    return NULL;
}
