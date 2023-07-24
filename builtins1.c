#include "shell.h"

/**
 * execute_builtin - Execute the given built-in command.
 * @args: The array of command arguments.
 *
 * Return: 1 if the command is a built-in and is executed, 0 otherwise.
 */
int execute_builtin(char **args)
{
	if (args[0] == NULL)
		return 0;

	if (strcmp(args[0], "exit") == 0)
	{
		// Add your implementation for the exit command here
		// ...
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		return cd_builtin(args);
	}
	else if (strcmp(args[0], "setenv") == 0)
	{
		return setenv_builtin(args);
	}
	else if (strcmp(args[0], "unsetenv") == 0)
	{
		return unsetenv_builtin(args);
	}
	else
	{
		return 0;
	}
}

/**
 * cd_builtin - Implement the cd (change directory) built-in command.
 * @args: The array of command arguments (should be "cd [DIRECTORY]").
 *
 * Return: 1 on success, -1 on failure.
 */
int cd_builtin(char **args)
{
	char *dir;
	char cwd[LINE_BUFFER_SIZE];

	if (args[1] == NULL)
	{
		dir = getenv("HOME");
		if (!dir)
		{
			fprintf(stderr, "cd: No HOME environment variable.\n");
			return (-1);
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		dir = getenv("OLDPWD");
		if (!dir)
		{
			fprintf(stderr, "cd: No OLDPWD environment variable.\n");
			return (-1);
		}
	}
	else
	{
		dir = args[1];
	}

	if (chdir(dir) != 0)
	{
		perror("cd");
		return (-1);
	}

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (-1);
	}

	/* Update PWD environment variable */
	if (setenv("PWD", cwd, 1) != 0)
	{
		perror("setenv");
		return (-1);
	}

	return (1);
}
