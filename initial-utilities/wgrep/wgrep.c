#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

char *word;
void handle_file(FILE *fp)
{
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
    {
        if (strstr(buffer, word) != NULL)
        {
            printf("%s", buffer);
        }
    }
    fclose(fp);
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }

    word = argv[1];

    if (argc == 2)
    {
        handle_file(stdin);
    }
    else
    {

        for (int file_index = 2; file_index < argc; file_index++)
        {
            char *file_name = argv[file_index];
            FILE *fp = fopen(file_name, "r");
            if (fp == NULL)
            {
                printf("wgrep: cannot open file\n");
                return 1;
            }
            handle_file(fp);
        }
    }

    return 0;
}