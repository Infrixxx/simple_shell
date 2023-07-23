#include "shell.h"

int main(void)
{
char *command;

while (1)
{
display_prompt();
command = read_command();

if (!command)
{
printf("\n");
break;
}

execute_command(command);
free(command);
}

return (EXIT_SUCCESS);
}

/**
* display_prompt - Display the shell prompt
*/
void display_prompt(void)
{
printf("#cisfun$ ");
}

/**
* read_command - Read a command from the user
*
* Return: The command entered by the user or NULL on "end of file" (Ctrl+D)
*/
char *read_command(void)
{
char *buffer = NULL;
size_t bufsize = 0;
int characters;

characters = getline(&buffer, &bufsize, stdin);

if (characters == EOF)
{
free(buffer);
return (NULL);
}

buffer[characters - 1] = '\0'; /* Remove the trailing newline */
return (buffer);
}

/**
* execute_command - Execute the given command
* @command: The command to execute
*/
void execute_command(char *command)
{
if (check_executable(command))
{
pid_t pid = fork();

if (pid == 0) /* Child process */
{
if (execve(command, NULL, environ) == -1)
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
}

/**
* check_executable - Check if the given command is an executable
* @command: The command to check
*
* Return: 1 if executable is found, 0 otherwise
*/
int check_executable(char *command)
{
if (access(command, X_OK) == 0)
return (1);
else
{
printf("%s: No such file or directory\n", command);
return (0);
}
}
