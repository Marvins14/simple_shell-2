#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int main(void)
{
	char *user_input;
	size_t size = 80;
	size_t input_size;
	char **argv;
	char *filename;
	const char s[2] = " ";
	char *bin = "/bin/";
	char *cwd = "./";
	pid_t child;
	char *n;
	char *slash = "/";
	while (1)
	{
		printf("$ ");
		user_input = malloc(size * sizeof(char));
		if (!user_input)
			exit (1);
		input_size = getline(&user_input, &size, stdin);
		if (input_size == -1)
			exit (1);
		child = fork();
		if (child == 0)
		{
			n = find_path(user_input);
			printf("SHELL - N = %s\n", n);
			if (n != "no")
			{
				argv[0] = n;
				argv[1] = user_input;
				if (execve(argv[0], argv, NULL) == -1)
					return (-1);
			}
			else if (n == "no")
			{
				strcat(cwd, user_input);
				argv[0] = cwd;
				if (execve(argv[0], argv, NULL) == -1)
					return (-1);
			}
		}
		else
			wait(0);
	}
	return (0);
}
