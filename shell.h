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
	void (*builtin)(char **args, char *line, char **env);
} builtins_t;
void shell(int ac, char **av, char **env);
char *_getline(void);
char **split_line(char *line);
int execute_prog(char **args, char *line, char **env, int flow);
int check_for_builtins(char **args, char *line, char **env);
int launch_prog(char **args);
void exit_shell(char **args, char *line, char **env);
void env_shell(char **args, char *line, char **env);
int _strcmp(char *s1, char *s2);
char *find_path(char *args, char *tmp, char *er);
char *search_cwd(char *filename);
int builtins_checker(char **args);
int bridge(char *check, char **args);
#endif
