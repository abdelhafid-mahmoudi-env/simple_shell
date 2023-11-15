#include "main.h"

/**
 * display_environment - prints out the current environment
 * @ptrs: structure containing all malloced memory
 */
void display_environment(shell_t *ptrs)
{
    unsigned int i;
    char newline = '\n';

    (void)ptrs;
    if (environ == NULL)
        return;

    for (i = 0; environ[i] != NULL; i++)
    {
        size_t len = str_length(environ[i]);
        if (len != 0)
        {
            write(STDOUT_FILENO, environ[i], len);
            write(STDOUT_FILENO, &newline, 1);
        }
    }
}
