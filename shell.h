#ifndef SHELL
#define SHELL
/**
 * struct builtins - Has builtins and associated funcs
 * @arg: Builtins name
 * @builtin: Mathcing builtin func
 */
typedef struct builtins
{
	char *arg;
	void (*builtin)(char **args, char *line);
} builtins_t;
void shell(void);
char *_getline(void);
char **split_line(char *line);
int execute_prog(char **args, char *line);
int check_for_builtins(char **args, char *line);
int launch_prog(char **args);
void exit_shell(char **args, char *line);
int _strcmp(char *s1, char *s2);
char* find_path(char *args);
#endif
