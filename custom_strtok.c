#include "shell.h"

/**
 * custom_strtok - Tokenize a string into tokens based on delimiters.
 * @str: The string to tokenize.
 * @delimiters: The delimiters to use for tokenization.
 *
 * Return: A pointer to the next token, or NULL if no more tokens are found.
 */
char *custom_strtok(char *str, const char *delimiters)
{
    static char *next_token = NULL;
    char *token_start = NULL;

    if (str)
    {
        token_start = str;
    }
    else if (next_token)
    {
        token_start = next_token;
    }
    else
    {
        return NULL;
    }

    while (*token_start && strchr(delimiters, *token_start))
    {
        token_start++;
    }

    if (*token_start)
    {

        char *token_end = token_start;
        while (*token_end && !strchr(delimiters, *token_end))
        {
            token_end++;
        }

        if (*token_end)
        {
            *token_end = '\0';

            next_token = token_end + 1;
        }
        else
        {
            next_token = NULL;
        }

        return token_start;
    }
    else
    {
        next_token = NULL;
        return NULL;
    }
}
