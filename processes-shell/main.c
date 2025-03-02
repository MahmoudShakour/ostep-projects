#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "built-in/builtin.h"

#define MAX_TOKENS 100
#define DELIM " "

char **parse_input()
{
    char *command = NULL;
    size_t len = 0;
    int read = getline(&command, &len, stdin);
    if (read == -1)
    {
        exit(1);
    }

    size_t length = strlen(command);
    if (length > 0 && command[length - 1] == '\n')
    {
        command[length - 1] = '\0';
    }

    char **tokens = malloc(MAX_TOKENS * sizeof(char *));
    if (!tokens)
    {
        exit(1);
    }

    char *ptr = command;
    int idx = 0;
    char *token;

    while ((token = strsep(&ptr, DELIM)) != NULL)
    {
        if (*token == '\0')
            continue;

        tokens[idx++] = strdup(token);
    }
    tokens[idx] = NULL;

    return tokens;
}

int main(int argc, char *argv[])
{
    while (1)
    {
        printf("wish> ");
        char **tokens = parse_input();
        if (!tokens)
        {
            exit(1);
        }

        if (is_builtin_command(tokens))
        {
            handle_builtin_command(tokens);
        }
        else
        {
            int rc = fork();
            if (rc == 0)
            {
                char *bin = argv[1];
                execv("/bin/ls", argv);
            }
            else
            {
                wait(NULL);
            }
        }
    }
}