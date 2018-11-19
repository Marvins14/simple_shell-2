#ifndef SHELL
#define SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#define TOKENS_BUFFER_SIZE 64
#define LINE_SIZE 1024
#define TOKEN_DELIMITERS " \t\r\n\a"


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
int execute_prog(char **args, char *line, char **env);
int check_for_builtins(char **args, char *line, char **env);
int launch_prog(char **args);
void exit_shell(char **args, char *line, char **env);
void env_shell(char **args, char *line, char **env);
int _strcmp(char *s1, char *s2);
char *find_path(char *args, char *tmp, char *er);
char *search_cwd(char *filename);
int bridge(char *check, char **args);
void prompt(void);
int builtins_checker(char **args);
char *save_path(char *tmp, char *path);
#endif
