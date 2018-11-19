#include "shell.h"

/**
 * execute_prog - Executes binary or builtin
 * @args: Argument buffer
 * @line: Line buffer
 * Return: 1 if success
 */
int execute_prog(char **args, char *line)
{
	int status;

	if (args[0] == NULL)
		return (1);
	if (check_for_builtins(args, line) == 1)
		return (1);
	status = launch_prog(args);
	return (status);
}
