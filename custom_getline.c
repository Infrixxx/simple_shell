#include "shell.h"

#define BUFFER_SIZE 1024

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
            return NULL; // End of input or error occurred
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

        // If the line length exceeds BUFFER_SIZE, realloc the line
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

    // If all characters are read from the buffer but line is not yet complete
    if (buffer_index >= characters_read)
    {
        characters_read = 0;
        buffer_index = 0;
    }

    return line; // Return the line read
}
