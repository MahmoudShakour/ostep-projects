#include "exit.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int validate_exit_command(char **tokens)
{
    return tokens[1] == NULL;
}

void handle_exit_command(char **tokens)
{
    int is_valid = validate_exit_command(tokens);
    if (!is_valid)
    {
        char error_message[30] = "An error has occurred\n";
        write(STDERR_FILENO, error_message, strlen(error_message));
        return;
    }
    exit(0);
}
