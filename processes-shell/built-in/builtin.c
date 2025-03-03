#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "builtin.h"
#include "exit.h"
#include "cd.h"
#include "path.h"


void init_builtin_commands(){
    init_path_command();
}

int is_builtin_command(char **tokens)
{
    if (strcmp(tokens[0], "exit") == 0)
        return 1;
    if (strcmp(tokens[0], "cd") == 0)
        return 1;
    if (strcmp(tokens[0], "path") == 0)
        return 1;
    return 0;
}

void handle_builtin_command(char **tokens)
{
    if (strcmp(tokens[0], "exit") == 0)
    {
        handle_exit_command(tokens);
    }
    if (strcmp(tokens[0], "cd") == 0)
    {
        handle_cd_command(tokens);
    }
    if (strcmp(tokens[0], "path") == 0)
    {
        handle_path_command(tokens);
    }
}