#include "shell.h"

/**
 * exit_shell - This will run the builtin exit
 * @line: Line buffer of user input
 * @args: Arguments from user
 * Return: Void
 */
void exit_shell(char **args, char *line, char **env)
{
	free(args);
	free(line);
	(void)env;
	exit(98);
}
void env_shell(char **args, char *line, char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	(void)args;
	(void)line;
}
