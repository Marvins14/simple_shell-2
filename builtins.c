#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
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
