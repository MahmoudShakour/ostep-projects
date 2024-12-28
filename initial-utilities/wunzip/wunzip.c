#include <stdio.h>

int process_file(char *file_name)
{
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        return 1;
    }
    int number;
    char character;

    while (fread(&number, sizeof(int), 1, fp) > 0 && fread(&character, sizeof(char), 1, fp) > 0)
    {

        for (int i = 0; i < number; i++)
            printf("%c", character);
    }
    fclose(fp);
    return 0;
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        char *file_name = argv[i];
        if (process_file(file_name) != 0)
        {
            printf("cannot open file\n");
            return 1;
        }
    }
}