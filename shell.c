#include "shell.h"

#define LINE_SIZE 1024
#define TOKENS_BUFFER_SIZE 64

/**
 * shell - Infinite loop that runs shell
 * @ac: Arg count
 * @av: args passed to shell at beginning of prog
 * Return: Void
 */
void shell(int ac, char **av)
{
	char *line;
	char **args;
	int status = 1;
	char *tmp = NULL;
	char *er;
	char *filename;
	int flow;

	do {
		prompt();
		line = _getline();
		args = split_line(line);
		flow = bridge(args[0], args, line);
		if (flow == 2)
		{
			filename = args[0];
			args[0] = find_path(args[0], tmp, er);
			if (args[0] == er)
			{
				args[0] = search_cwd(filename);
			}
		}
		status = execute_prog(args, line);
		free(line);
		free(args);
	} while (status);
	if (!ac)
		(void)ac;
	if (!av)
		(void)av;
}
