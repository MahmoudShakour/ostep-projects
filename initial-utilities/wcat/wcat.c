#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE (1024)

int main(int argc, char *argv[])
{

    for (int file_number = 1; file_number < argc; file_number++)
    {
        char *file_name = argv[file_number];
        FILE *fp = fopen(file_name, "r");
        if (fp == NULL)
        {
            printf("wcat: cannot open file\n");
            exit(1);
        }
        char buffer[BUFFER_SIZE];
        while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
        {
            printf("%s", buffer);
        }
        fclose(fp);
    }
}