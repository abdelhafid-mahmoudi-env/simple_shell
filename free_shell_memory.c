#include "main.h"

/**
 * free_shell_memory - Frees memory allocated for the shell_t struct.
 * @shell_ptrs: Pointer to the shell_t structure.
 */
void free_shell_memory(shell_t *shell_ptrs)
{
    if (shell_ptrs)
    {
        free(shell_ptrs->path_values);
        free(shell_ptrs->input);
        free(shell_ptrs->input_token);
        free(shell_ptrs->modify_path);
    }
}
