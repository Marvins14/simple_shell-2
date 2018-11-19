#include "shell.h"
/**
 * find_path - finds path
 * @filename: file name
 * @tmp: temp
 * @er: er
 * Return: path
 */

char *find_path(char *filename, char *tmp, char *er)
{
	DIR *dir;
	struct dirent *sd;
	char *file_path, *path, *ret;
	int len = 0, i = 0;

	printf("I am in find path\n");
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
					free(tmp);
					return (ret);
				}
			}
		}
		closedir(dir);
		file_path = strtok(NULL, ":");
	}
	path = NULL;
	free(tmp);
	return (er);
}
