#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "built-in/builtin.h"
#include "non-built-in/non_builtin.h"
#include "built-in/path.h"

#define MAX_TOKENS 100
#define DELIM " "

char *get_line()
{
    char *command = NULL;
    size_t len = 0;
    int read = getline(&command, &len, stdin);
    if (read == -1)
    {
        char error_message[30] = "An error has occurred\n";
        write(STDERR_FILENO, error_message, strlen(error_message));
    }

    size_t length = strlen(command);
    if (length > 0 && command[length - 1] == '\n')
    {
        command[length - 1] = '\0';
    }
    return command;
}

char **parse_command(char *command)
{
    char **tokens = malloc(MAX_TOKENS * sizeof(char *));
    if (!tokens)
    {
        char error_message[30] = "An error has occurred\n";
        write(STDERR_FILENO, error_message, strlen(error_message));
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

void handle_tokens(char **tokens, char **argv)
{
    if (is_builtin_command(tokens))
    {
        handle_builtin_command(tokens);
    }
    else if (get_can_run_non_builtin_functions())
    {
        handle_non_builtin_command(tokens, get_paths());
    }
    else
    {
        char error_message[30] = "An error has occurred\n";
        write(STDERR_FILENO, error_message, strlen(error_message));
    }
}

void init()
{
    init_builtin_commands();
}

int main(int argc, char *argv[])
{
    init();
    if (argc == 2)
    {
        char *file_name = argv[1];
        FILE *file = fopen(file_name, "r");
        char buffer[100];
        while (fgets(buffer, 100, file) != NULL)
        {
            size_t length = strlen(buffer);
            if (length > 0 && buffer[length - 1] == '\n')
            {
                buffer[length - 1] = '\0';
            }
            char **tokens = parse_command(buffer);
            if (!tokens)
            {
                char error_message[30] = "An error has occurred\n";
                write(STDERR_FILENO, error_message, strlen(error_message));
            }
            handle_tokens(tokens, argv);
        }
        exit(0);
    }

    while (1)
    {
        printf("wish> ");
        char *command = get_line();
        char **tokens = parse_command(command);
        if (!tokens)
        {
            char error_message[30] = "An error has occurred\n";
            write(STDERR_FILENO, error_message, strlen(error_message));
        }

        handle_tokens(tokens, argv);
    }
    return 0;
}