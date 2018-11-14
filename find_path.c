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
	char *cwd = ".";
	char *file = NULL;
	int i = 0;
	const char delim[2] = ":";
	char *p;
	char *built_ins;
	int n = 0;
	char s[2] = " ";

	p = getenv("PATH");
	built_ins = strtok(p, ":");
	printf("%s\n", built_ins);
	while (built_ins)
	{
		dir = opendir(built_ins);
		printf("%s\n", built_ins);
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
				if((sd->d_name[i] != s[0]) && (sd->d_name[i] != user_input[i]))
					i = 0;
				if (sd->d_name[i] != user_input[i])
				{
					i = 0;
					break;
				}
			}
			if (i > 0)
			{
				closedir(dir);
				return(built_ins);
			}
			built_ins = strtok(NULL, ":");
		}
		closedir(dir);
	}
	dir = opendir(cwd);
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
