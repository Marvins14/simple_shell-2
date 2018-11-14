#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define TOKENS_BUFFER_SIZE 64
#define TOKEN_DELIMITERS " \t\r\n\a"

/**
 * _getline - Gets line of user input
 * Return: Pointer to buffer of user input
 */
char *_getline(void)
{
	int temp;
	char *line = NULL;
	size_t size = 0;

	temp = getline(&line, &size, stdin);
	if (temp == EOF)
	{
		write(1, "\n", 1);
		exit(1);
	}
	return (line);
}
/**
 * split_line - Splits line into args
 * @line: Line of user input
 * Return: Array of args of user input
 */
char **split_line(char *line)
{
	size_t buffer_size = TOKENS_BUFFER_SIZE;
	char **tokens = malloc(sizeof(char *) * buffer_size);
	char *token;
	int pos = 0;

	if (!tokens)
	{
		perror("Could not allocate space for tokens\n");
		exit(2);
	}
	token = strtok(line, TOKEN_DELIMITERS);
	while (token)
	{
		tokens[pos] = token;
		token = strtok(NULL, TOKEN_DELIMITERS);
		pos++;
	}
	tokens[pos] = NULL;
	return (tokens);
}
/**
 * check_for_builtins - Checks for builtins
 * @args: Arguments passed from prompt
 * @line: Buffer with line of input from user
 * Return: 1 if builtins exist, 0 if they don't
 */
int check_for_builtins(char **args, char *line)
{
	builtins_t list[] = {
		{"exit", exit_shell},
		{NULL, NULL}
	};
	int i;

	for (i = 0; list[i].arg != NULL; i++)
	{
		if (_strcmp(list[i].arg, args[0]) == 0)
		{
			list[i].builtin(args, line);
			return (1);
		}
	}
	return (0);
}
/**
 * launch_prog - Forks and launches unix cmd
 * @args: Args for cmd
 * Return: 1 on success
 */
int launch_prog(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("Failed to execute command\n");
			exit(3);
		}
	}
	else if (pid < 0)
	{
		perror("Error forking\n");
		exit(4);
	}
	else
	{
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && WIFSIGNALED(status));
	}
	(void)wpid;
	return (1);
}
