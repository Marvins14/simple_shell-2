#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

char* find_path(char *user_input)
{
	DIR *dir;
	struct dirent *sd;
	char *file = NULL;
	int i = 0;
	const char delim[2] = ":";
	char *p;
	char *built_ins;
	int n = 0;
	char s[2] = " ";
	int a = 0;

	while (user_input[a])
		a++;
	p = getenv("PATH");
	built_ins = strtok(p, ":");
	while (built_ins)
	{
		dir = opendir(built_ins);
		if (!dir)
		{
			printf("Error! Unable to open directory.\n");
			exit(1);
		}
		while (sd = readdir(dir))
		{
			printf("FIND - %s/", built_ins);
			printf("%s\n", sd->d_name);
			for (i = 0; sd->d_name[i] && user_input[i]; i++)
			{
				if (sd->d_name[i] != user_input[i])
					break;
				if (sd->d_name[i] == user_input[i])
				{
					printf("A: %d %s\n", a, user_input);
					printf("I: %d\n%s", (i + 1), sd->d_name);
				}
				if (((i + 1) == (a - 1)) && !(sd->d_name[i +1]))
					return (built_ins);
			}
		}
		closedir(dir);
		built_ins = strtok(NULL, ":");
	}
	dir = opendir(".");
	if (!dir)
	{
		printf("Error! Unable to open directory.\n");
		exit(1);
	}
	while (sd = readdir(dir))
	{
		while (sd->d_name[i])
		{
			if (sd->d_name[i] == user_input[i])
				i++;
			else
			{
				i = 0;
				break;
			}
		}
		if (i > 0)
		{
			closedir(dir);
			return("./");
		}
	}
	closedir(dir);
	return ("no");
}
