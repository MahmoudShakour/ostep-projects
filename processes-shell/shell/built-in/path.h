#ifndef PATH_H
#define PATH_H


int handle_path_command(char **tokens);
void init_path_command();
char** get_paths();
int get_can_run_non_builtin_functions();
#endif