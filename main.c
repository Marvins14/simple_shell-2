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
 * main - Entry point for shell, handles args to shell
 * @ac: Arg count
 * @av: Arr of args
 * Return: 0;
 */
int main(int ac, char **av)
{
	if (!ac)
		(void)ac;
	if (!av)
		(void)av;
	shell(ac, av);
	return (0);
}

