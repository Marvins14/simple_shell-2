#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

char* find_path(char *filename)
{
	DIR *dir;
	struct dirent *sd;
	char *file_path;
	char *path;
	int len = 0;
	int i = 0;
	int execute;
	char *ret;

	while (filename[len])
		len++;
	path = getenv("PATH");
	file_path = strtok(path, ":");
	while (file_path)
	{
		dir = opendir(file_path);
		if (!dir)
		{
			printf("Error! Unable to open directory.\n");
			exit(1);
		}
		while (sd = readdir(dir))
		{
			for (i = 0; sd->d_name[i] && filename[i]; i++)
			{
				if (sd->d_name[i] != filename[i])
					break;
				if (((i + 1) == (len - 1)) && !(sd->d_name[i + 1]))
				{
					ret = strcat(file_path, "/");
					ret = strcat(ret, filename);
					execute = access(ret);
					if (execute == 0)
					{
						closedir(dir);
						return (ret);
					}
				}
			}
		}
		closedir(dir);
		file_path = strtok(NULL, ":");
	}
	ret = check_cwd(filename, len);
	if (ret != "error")
		return (ret);
	return ("error");
}

char* check_cwd(char *filename, int len)
{
	DIR *dir;
	struct dirent *sd;
	char *ret;
	int i = 0;
	int execute;

	dir = opendir(".");
	if (!dir)
	{
		printf("Error! Unable to open directory.\n");
		exit(1);
	}
	while (sd = readdir(dir))
	{
		for (i = 0; sd->d_name[i] && filename[i]; i++)
		{
			if (sd->d_name[i] != filename[i])
				break;
			if (((i + 1) == (len - 1)) && !(sd->d_name[i + 1]))
			{
				ret = "./";
				ret = strcat(ret, filename);
				execute = access(ret);
				if (execute == 0)
				{
					closedir(dir);
					return (ret);
				}
			}
		}
	}
	return ("error");
}
