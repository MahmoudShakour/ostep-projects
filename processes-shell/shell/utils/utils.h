#ifndef UTILS_H
#define UTILS_H

void throw_error();
char *read_line();
char **parse_command(char *command);
void execute_command(char **tokens);
int check_multiple_commands(char *command);
char **split_multiple_commands(char *command);
void handle_command(char *command);


#endif
