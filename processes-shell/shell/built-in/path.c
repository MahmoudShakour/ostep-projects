#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define MAX_NUMBER_OF_PATHS 100
#define MAX_PATH_SIZE 100

char *paths[MAX_NUMBER_OF_PATHS];
int can_run_non_builtin_functions = 1;

void init_path_command()
{
    paths[0] = malloc(MAX_PATH_SIZE * sizeof(char));
    paths[0] = strdup("/bin");
}

void handle_path_command(char **tokens)
{
    if (tokens[1] == NULL)
    {
        can_run_non_builtin_functions = 0;
        return;
    }
    can_run_non_builtin_functions = 1;
    for (int i = 1; tokens[i]; i++)
    {
        paths[i] = malloc(MAX_PATH_SIZE * sizeof(char));
        paths[i] = strdup(tokens[i]);
    }
}

char **get_paths()
{
    return paths;
}

int get_can_run_non_builtin_functions()
{
    return can_run_non_builtin_functions;
}