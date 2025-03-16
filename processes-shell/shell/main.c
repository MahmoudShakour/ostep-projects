#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "utils/utils.h"
#include "built-in/builtin.h"

#define MAX_COMMAND_SIZE 100

void init()
{
    init_builtin_commands();
}

int main(int argc, char *argv[])
{
    init();

    if (argc > 1)
    {
        for (int i = 1; argv[i]; i++)
        {
            char *file_name = argv[i];
            FILE *file = fopen(file_name, "r");
            if (file == NULL)
            {
                throw_error();
                exit(1);
            }
            char buffer[MAX_COMMAND_SIZE];
            while (fgets(buffer, MAX_COMMAND_SIZE, file) != NULL)
            {
                size_t length = strlen(buffer);
                if (length > 0 && buffer[length - 1] == '\n')
                {
                    buffer[length - 1] = '\0';
                }
                handle_command(buffer);
            }
        }
    }
    else
    {
        while (1)
        {
            printf("wish> ");
            char *command = read_line();
            handle_command(command);
        }
    }
    return 0;
}