#include "main.h"

/**
 * shell_num_builtins - Return the number of built-in commands
 * Return: Number of built-in commands
 */
int shell_num_builtins(void)
{
	static char *builtin_str[] = {
		"cd",
		"help",
		"exit",
		"env"
	};

	return (sizeof(builtin_str) / sizeof(char *));
}

/**
 * builtin_func - Get the function associated with a built-in command
 * @index: Index of the built-in command
 * Return: Function pointer to the built-in command
 */
int (*builtin_func(int index))(char **) {
	static int (*func[]) (char **) = {
		&cmd_cd,
		&cmd_help,
		&cmd_exit,
		&cmd_env
	};

	return (func[index]);
}

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
		if (execvp(args[0], args) == -1)
		{
			perror("lsh");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0)
	{
		/* Error forking */
		perror("lsh");
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
 * execute - Executes a shell command or launches a program
 * @args: Arguments array
 * Return: Status code
 */
int execute(char **args, char *builtin_str[])
{
	(void)builtin_str;
	int i;
	int num_builtins = shell_num_builtins();

	if (args[0] == NULL)
	{
		/* An empty command was entered */
		return (1);
	}

	for (i = 0; i < num_builtins; i++)
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
		{
			return ((*builtin_func(i))(args));
		}
	}

	return (launch(args));
}

/**
 * command_exists - Checks if a command exists in the PATH
 * @cmd: The command to check
 * Return: 1 if command exists, 0 otherwise
 */
int command_exists(char *cmd)
{
	struct stat buffer;

	return (stat(cmd, &buffer) == 0 && (buffer.st_mode & S_IXUSR));
}
