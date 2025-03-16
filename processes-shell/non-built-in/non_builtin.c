#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "non_builtin.h"

char *generate_full_path(char **tokens, char *path)
{
    char *full_path = malloc(100 * sizeof(char));
    full_path = strdup(path);
    strcat(full_path, strdup("/"));
    char *bin = tokens[0];
    strcat(full_path, bin);
    return full_path;
}

void handle_non_builtin_command(char **tokens, char **paths)
{
    int rc = fork();
    if (rc == 0)
    {
        for (int i = 0; paths[i]; i++)
        {

            char *path = paths[i];
            char *full_path = generate_full_path(tokens, path);

            if (access(full_path, X_OK) != 0)
                continue;

            int read = execv(full_path, tokens);
            if (read == -1)
            {
                char error_message[30] = "An error has occurred\n";
                write(STDERR_FILENO, error_message, strlen(error_message));
            }
        }
        char error_message[30] = "An error has occurred\n";
        write(STDERR_FILENO, error_message, strlen(error_message));
    }
}