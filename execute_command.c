#include "main.h"

/**
 * execute_command - Execute a command specified by the user.
 * @shell_ptrs: Pointer to the shell_t structure containing allocated memory.
 * @filename: Name of the file being executed.
 * @envp: Environment variables.
 * Return: The errno value.
 */
int execute_command(shell_t *shell_ptrs, char *filename, char **envp)
{
	pid_t child_pid;
	char **input_token = shell_ptrs->input_token;
	int status = 0;

	if (input_token[0] == NULL)
		return (status);
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (child_pid == 0)
	{
		child_process(shell_ptrs, filename, envp);
	}
	else
	{
		wait(&status);
		errno = WEXITSTATUS(status);
		return (errno);
	}
	return (errno);
}

/**
 * child_process - Logic for the child process in execute_command.
 * @shell_ptrs: Pointer to the shell_t structure containing allocated memory.
 * @filename: Name of the file being executed.
 * @envp: Environment variables.
 */
void child_process(shell_t *shell_ptrs, char *filename, char **envp)
{
	char **input_token = shell_ptrs->input_token;
	char **path = shell_ptrs->path_values;
	char *command = input_token[0];
	char *input_org, *executable;

	input_org = string_duplicate(command);
	if (input_org == NULL)
	{
		perror("string_duplicate");
		exit(1);
	}
	executable = find_executable_path(path, command);
	if (executable != NULL)
	{
		if (execve(executable, input_token, envp) == -1)
			perror(filename);
		free(executable);
	}
	else
	{
		errno = 127;
		print_command_not_found_error(input_org, filename);
	}
	free(input_org);
	free_shell_memory(shell_ptrs);
	_exit(errno);
}
