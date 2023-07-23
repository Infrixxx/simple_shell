#include "shell.h"

#define BUFFER_SIZE 1024
/**
*custom_getline - Read a line of input from the standard input.
* Return: On success, returns a pointer to the line read from input.
*         On failure or end-of-file, returns NULL.
*/

char *custom_getline(void)
{
static char buffer[BUFFER_SIZE];
static int buffer_index = 0;
static int characters_read = 0;

char *line = NULL;
int i = 0;

if (characters_read == 0)
{
characters_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
buffer_index = 0;

if (characters_read <= 0)
{
return NULL;
}
}

line = malloc(BUFFER_SIZE * sizeof(char));
if (!line)
{
perror("Memory Allocation Error");
return NULL;
}

while (buffer_index < characters_read)
{
if (buffer[buffer_index] == '\n')
{
line[i] = '\0'; // Null-terminate the line
buffer_index++;
return line; // Return the line read
}
line[i] = buffer[buffer_index];
i++;
buffer_index++;

if (i >= BUFFER_SIZE)
{
line = realloc(line, (i + BUFFER_SIZE) * sizeof(char));
if (!line)
{
perror("Memory Allocation Error");
return NULL;
}
}
}

if (buffer_index >= characters_read)
{
characters_read = 0;
buffer_index = 0;
}

return line; 
}
