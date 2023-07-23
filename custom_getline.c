#include "shell.h"

/**
 * read_input - Read input from the standard input into a buffer.
 * Return: Number of characters read, or -1 on failure.
 */

static int read_input(char *buffer, int buffer_size)
{
        int characters_read = read(STDIN_FILENO, buffer, buffer_size);

        if (characters_read <= 0)
        {
                return (-1);
        }
        return (characters_read);
}

/**
 * process_input - Process the input buffer and extract a line.
 * Return: Pointer to the line read from input, or NULL on failure.
 */

static char *process_input(char *buffer, int buffer_size)
{
        static int buffer_index = 0;
        char *line = NULL;
        int i = 0;

        if (buffer_index == 0)
        {
                int characters_read = read_input(buffer, buffer_size);
                if (characters_read <= 0)
                {
                        return (NULL);
                }
        }

        line = malloc(LINE_BUFFER_SIZE * sizeof(char));
        if (!line)
        {
                perror("Memory Allocation Error");
                return (NULL);
        }

        while (buffer_index < buffer_size)
        {
                if (buffer[buffer_index] == '\n')
                {
                        line[i] = '\0';
                        buffer_index++;
                        return (line);
                }
                line[i] = buffer[buffer_index];
                i++;
                buffer_index++;

                if (i >= LINE_BUFFER_SIZE)
                {
                        line = realloc(line, (i + LINE_BUFFER_SIZE) * sizeof(char));
                        if (!line)
                        {
                                perror("Memory Allocation Error");
                                return (NULL);
                        }
                }
        }
        if (buffer_index >= buffer_size)
        {
                buffer_index = 0;
        }
        return (line);
}

/**
 * custom_getline - Read a line of input from the standard input.
 * Return: On success, returns a pointer to the line read from input.
 *         On failure or end-of-file, returns NULL.
 */
char *custom_getline(void)
{
        static char buffer[BUFFER_SIZE];
        int characters_read = read_input(buffer, BUFFER_SIZE);
        if (characters_read <= 0)
        {
                return (NULL);
        }
        return (process_input(buffer, characters_read));
}
