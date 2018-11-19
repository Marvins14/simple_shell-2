#include "shell.h"

/**
 * exit_shell - This will run the builtin exit
 * @line: Line buffer of user input
 * @args: Arguments from user
 * Return: Void
 */
void exit_shell(char **args, char *line)
{
	free(args);
	free(line);
	exit(98);
}
