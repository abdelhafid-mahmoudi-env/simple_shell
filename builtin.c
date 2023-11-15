#include "main.h"

/**
 * cmd_exit - Builtin command that exits the shell
 * @args: List of arguments (unused)
 * Return: Status code to exit the shell
 */
int cmd_exit(char **args __attribute__((unused)))
{
	return (0);
}

/**
 * cmd_env - Builtin command that prints the environment variables
 * @args: List of arguments (unused)
 * Return: Always returns 1, to continue executing
 */
int cmd_env(char **args __attribute__((unused)))
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
	return (1);
}

/**
 * cmd_cd - Builtin command that changes the current directory
 * @args: List of arguments where args[1] is the directory
 * Return: Always returns 1, to continue executing
 */
int cmd_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "lsh: expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("lsh");
		}
	}

	return (1);
}

/**
 * cmd_help - Builtin command that prints help information
 * @args: List of arguments (unused)
 * @builtin_str: Array of built-in command strings
 * Return: Always returns 1, to continue executing
 */
int cmd_help(char **args __attribute__((unused)), char **builtin_str)
{
	int i;

	printf("Simple Shell by ABDELHAFID ET AMINE\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");

	for (i = 0; i < shell_num_builtins(); i++)
	{
		printf("  %s\n", builtin_str[i]);
	}

	return (1);
}
