#include "main.h"

/**
 * shell_num_builtins - Returns the number of built-in shell commands.
 *
 * Return: The number of built-in commands.
 */
int shell_num_builtins(void)
{
	return (4);
}

/**
 * launch - Launches a new process to execute a command.
 * @args: An array of strings representing the command and its arguments.
 *
 * Return: Always returns 1.
 */
int launch(char **args)
{
	pid_t pid;
	int status;

	if (!command_exists(args[0]))
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return (1);
	}

	pid = fork();

	if (pid == 0)
	{
		if (execv(args[0], args) == -1)
		{
			perror(args[0]);
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Forking error");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}

/**
 * execute - Executes a command, either a built-in or an external one.
 * @args: An array of strings representing the command and its arguments.
 * @builtin_str: An array of strings representing built-in commands.
 *
 * Return: Always returns 1.
 */
int execute(char **args, char **builtin_str)
{
	int i;

	if (args[0] == NULL || args[0][0] == '\0')
	{
		return (1);
	}

	if (args[1] != NULL)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return (1);
	}

	for (i = 0; i < 4; i++)
	{
		if (strcmp(args[0], "cd") == 0)
		{
			return (cmd_cd(args));
		}
		else if (strcmp(args[0], "help") == 0)
		{
			return (cmd_help(args, builtin_str));
		}
		else if (strcmp(args[0], "exit") == 0)
		{
			return (cmd_exit(args));
		}
		else if (strcmp(args[0], "env") == 0)
		{
			return (cmd_env(args));
		}
	}

	return (launch(args));
}

/**
 * command_exists - Checks if a command exists in the system.
 * @cmd: The command to check.
 *
 * Return: 1 if the command exists, 0 otherwise.
 */
int command_exists(char *cmd)
{
	struct stat buffer;

	return (stat(cmd, &buffer) == 0 && (buffer.st_mode & S_IXUSR));
}
