#ifndef BUILTIN_H
#define BUILTIN_H

void handle_exit_command();
int is_builtin_command(char **tokens);
void handle_builtin_command(char **tokens);

#endif