#ifndef _SHELL_H_
#define _SHELL_H_

/*# Libraries#*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*# MACROS #*/

#define BUFFER_SIZE 1024

/*Function prototypes*/
void display_prompt();
char *read_command();
void execute_command(char *command);

#endif
