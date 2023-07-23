#include "shell.h"

/**
* execute_command_with_args - Execute the command with arguments
* @args: The array of strings containing the command and its arguments
*/

void execute_command_with_args(char **args)
{
pid_t pid = fork();

if (pid == 0) /* Child process */
{
if (execve(args[0], args, environ) == -1)
{
perror("Error");
exit(EXIT_FAILURE);
}
}
else if (pid < 0)
{
perror("Fork Error");
}
else
{
wait(NULL); /* Parent process waits for child to complete */
}
}
