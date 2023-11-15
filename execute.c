#include "main.h"

/**
 * launch - Launches a program
 * @args: Arguments array
 * Return: Status code
 */
int launch(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		if (execve(args[0], args, environ) == -1)
		{
			perror(args[0]);
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0)
	{
		/* Error forking */
		perror(args[0]);
	} else
	{
		/* Parent process */
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}

/**
 * execute - Executes a shell command
 * @args: Arguments array
 * Return: Status code
 */
int execute(char **args)
{
	if (args[0] == NULL)
	{
		/* An empty command was entered */
		return (1);
	}

	return (launch(args));
}

