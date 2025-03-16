#include "redirect.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int redirection_in_command(char **tokens)
{
    int counter = 0;
    for (int i = 0; tokens[i]; i++)
    {
        if (strcmp(tokens[i], ">") == 0)
            counter++;
    }
    return counter;
}

int number_of_tokens(char **tokens)
{
    int i = 0;
    while (tokens[i])
        i++;
    return i;
}

int validate_redirection(char **tokens)
{
    int command_length = number_of_tokens(tokens);
    if ((command_length > 2) && (strcmp(tokens[command_length - 2], ">") == 0) && redirection_in_command(tokens) == 1)
    {
        tokens[command_length - 2] = "\0";
        return 1;
    }
    return 0;
}

int redirect_to_file(char **tokens)
{

    int command_length = number_of_tokens(tokens);
    char *file_name = strdup(tokens[command_length - 1]);
    int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        char error_message[30] = "An error has occurred\n";
        write(STDERR_FILENO, error_message, strlen(error_message));
        return -1;
    }
    tokens[command_length - 1] = NULL;
    tokens[command_length - 2] = NULL;
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
    close(fd);
    return fd;
}

int validate_and_redirect(char **tokens)
{
    int is_valid = validate_redirection(tokens);

    if (!is_valid)
    {
        char error_message[30] = "An error has occurred\n";
        write(STDERR_FILENO, error_message, strlen(error_message));
        return -1;
    }
    return redirect_to_file(tokens);
}
