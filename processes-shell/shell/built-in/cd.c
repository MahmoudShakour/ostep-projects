#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "cd.h"
#include "string.h"

void handle_cd_command(char **tokens)
{
    int is_valid = validate_cd_command(tokens);
    if (!is_valid)
        return;
    char *path = strdup(tokens[1]);

    if (chdir(path) == -1)
    {
        char error_message[30] = "An error has occurred\n";
        write(STDERR_FILENO, error_message, strlen(error_message));
    }
}

int validate_cd_command(char **tokens)
{

    if (tokens[1] == NULL || tokens[2] != NULL)
    {
        char error_message[30] = "An error has occurred\n";
        write(STDERR_FILENO, error_message, strlen(error_message));
        return 0;
    }
    return 1;
}