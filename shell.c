#include "shell.h"

/**
 * main - Simple UNIX command line interpreter.
 *
 * Return: Always 0.
 */

int main(void)
{
	char buffer[BUFFER_SIZE];
	char *args[2];
	int status;
	pid_t child_pid;

	while (1)
	{
		printf("#cisfun$ ");

		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		buffer[strcspn(buffer, "\n")] = '\0';
		if (strcmp(buffer, "exit") == 0)
		{
			break;
		}
		child_pid = fork();
		if (child_pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			args[0] = buffer;
			args[1] = NULL;
			if (execve(args[0], args, environ) == -1)
			{
				perror(args[0]);
			}
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(child_pid, &status, 0);
		}
	}
	return (EXIT_SUCCESS);
}
