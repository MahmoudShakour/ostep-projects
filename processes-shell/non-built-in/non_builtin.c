#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "non_builtin.h"

void handle_non_builtin_command(char **tokens)
{
    int rc = fork();
    if (rc == 0)
    {
        char path[100] = "/bin/";
        char *bin = tokens[0];
        strcat(path, bin);
        int read = execv(path, tokens);
        if (read == -1)
        {
            char error_message[30] = "An error has occurred\n";
            write(STDERR_FILENO, error_message, strlen(error_message));
        }
    }
    else
    {
        wait(NULL);
    }
}