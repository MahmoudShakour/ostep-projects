#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "cd.h"
#include "string.h"

void handle_cd_command(char **tokens)
{
    validate_cd_command(tokens);

    char *path = strdup(tokens[1]);

    if (chdir(path) == -1)
    {
        exit(1);
    }
}

void validate_cd_command(char **tokens)
{
    if (tokens[1] == NULL || tokens[2] != NULL)
    {
        exit(1);
    }
}