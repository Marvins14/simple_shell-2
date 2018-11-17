#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

char* find_path(char *filename)
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
	printf("getenv: %s\n", path);
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
	return ("error");
}
