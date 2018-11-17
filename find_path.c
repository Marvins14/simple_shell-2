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
					file_path = strcat(file_path, "/");
					file_path = strcat(file_path, filename);
					closedir(dir);
					return (file_path);
				}
			}
		}
		closedir(dir);
		file_path = strtok(NULL, ":");
	}
	return ("no\n");
}
