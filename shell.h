#ifndef SHELL
#define SHELL
void shell(void);
char *_getline(void);
char **split_line(char *line);
int launch_prog(char **args);
#endif
