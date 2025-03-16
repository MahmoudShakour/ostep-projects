#include "utils.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>


#include "../built-in/builtin.h"
#include "../non-built-in/non_builtin.h"
#include "../built-in/path.h"
#include "../redirection/redirect.h"

#define MAX_TOKENS 100
#define MAX_COMMAND_SIZE 100
#define DELIM " "

void throw_error()
{
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
}

char *read_line()
{
    char *command = NULL;
    size_t len = 0;
    int read = getline(&command, &len, stdin);
    if (read == -1)
    {
        throw_error();
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
        throw_error();
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

void execute_command(char **tokens)
{
    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stderr = dup(STDERR_FILENO);
    int fd_of_opened_file = -1;

    if (redirection_in_command(tokens))
    {
        fd_of_opened_file = validate_and_redirect(tokens);
        if (fd_of_opened_file == -1)
        {
            return;
        }
    }

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
        throw_error();
    }
    if (fd_of_opened_file != -1)
    {
        dup2(saved_stdout, STDOUT_FILENO);
        dup2(saved_stderr, STDERR_FILENO);
        close(saved_stdout);
        close(saved_stderr);
    }
}

int check_multiple_commands(char *command)
{
    for (int i = 0; command[i]; i++)
    {
        if (command[i] == '&')
        {
            return 1;
        }
    }
    return 0;
}

char **split_multiple_commands(char *command)
{
    char **commands = malloc(MAX_TOKENS * sizeof(char *));
    if (!commands)
    {
        throw_error();
    }

    char *ptr = command;
    int idx = 0;
    char *token;

    while ((token = strsep(&ptr, "&")) != NULL)
    {
        if (*token == '\0')
            continue;
        commands[idx++] = strdup(token);
    }
    commands[idx] = NULL;

    return commands;
}

void handle_command(char *command)
{
    char **commands = split_multiple_commands(command);
    for (int i = 0; commands[i]; i++)
    {
        char **tokens = parse_command(commands[i]);
        if (!tokens)
        {
            throw_error();
        }
        if (!tokens[0])
            continue;
        execute_command(tokens);
    }
    while (wait(NULL) > 0)
        ;
}
