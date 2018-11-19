#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

char* find_path(char *filename, char *tmp, char *er)
{
	DIR *dir;
	struct dirent *sd;
	char *file_path;
	char *path;
	int len = 0;
	int i = 0;
	char *ret;

	while (filename[len])
		len++;
	path = getenv("PATH");
	if (!tmp)
	{
		tmp = malloc(sizeof(char) * 100);
		while (path[i])
		{
			tmp[i] = path[i];
			i++;
			tmp[i] = '\0';
		}
		i = 0;
	}
	else
	{
		while (tmp[i])
		{
			path[i] = tmp[i];
			i++;
			path[i] = '\0';
		}
		i = 0;
	}
	file_path = strtok(tmp, ":");
	while (file_path)
	{
		dir = opendir(file_path);
		if (!dir)
		{
			printf("Error! Unable to open directory.\n");
			exit(1);
		}
		while ((sd = readdir(dir)))
		{
			for (i = 0; sd->d_name[i] && filename[i]; i++)
			{
				if (sd->d_name[i] != filename[i])
					break;
				if (i == (len - 1) && !(sd->d_name[i + 1]))
				{
					ret = strcat(file_path, "/");
					ret = strcat(ret, filename);
					path = NULL;
					closedir(dir);
					return (ret);
				}
			}
		}
		closedir(dir);
		file_path = strtok(NULL, ":");
	}
	path = NULL;
	return (er);
}
