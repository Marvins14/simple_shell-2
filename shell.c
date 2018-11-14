#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define LINE_SIZE 1024
#define TOKENS_BUFFER_SIZE 64

/**
 * shell - Infinite loop that runs shell
 * Return: Void
 */
void shell(void)
{
	char *line;
	char **args;
	int status;

	do {
		write(1, "$ ", 2);
		line = _getline();
		args = split_line(line);
		if (check_for_builtins(args, line) == 1)
			continue;
		status = launch_prog(args);
		free(line);
		free(args);
	} while (status);
}
