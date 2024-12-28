#include <stdio.h>
#include <string.h>
#define COMPRESSION_SIZE 1000000
#define BUFFER_SIZE 1000000

int compression_value[COMPRESSION_SIZE];
char compression_character[COMPRESSION_SIZE];
int compression_index;

int value;
char character = '\0';

void process_line(char *line)
{
    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == character)
        {
            value++;
        }
        else
        {
            compression_value[compression_index] = value;
            compression_character[compression_index] = character;
            compression_index++;
            value = 1;
            character = line[i];
        }
    }
}

int process_file(char *file_name)
{

    FILE *fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        return 1;
    }
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, fp) != NULL)
    {
        process_line(buffer);
    }
    return 0;
}
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        char *file_name = argv[i];
        if (process_file(file_name) != 0)
        {
            printf("wzip: cannot open file");
            return 1;
        }
    }

    for (int i = 1; i < compression_index; i++)
    {
        fwrite(&compression_value[i], sizeof(int), 1, stdout);
        fwrite(&compression_character[i], sizeof(char), 1, stdout);
    }

    fwrite(&value, sizeof(int), 1, stdout);
    fwrite(&character, sizeof(char), 1, stdout);
}