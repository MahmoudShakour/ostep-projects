#ifndef BUILTIN_H
#define BUILTIN_H

void init_builtin_commands();
int is_builtin_command(char **tokens);
void handle_builtin_command(char **tokens);

#endif