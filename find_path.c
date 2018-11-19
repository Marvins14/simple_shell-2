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
	int len = 0;

	while (filename[len])
		len++;
	path = getenv("PATH");
	tmp = save_path(tmp, path);
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
			ret = read_dir(er, sd, filename, len, file_path, tmp);
			if (ret != er)
			{
				closedir(dir);
				return (ret);
			}
		}
		closedir(dir);
		file_path = strtok(NULL, ":");
	}
	path = NULL;
	free(tmp);
	return (er);
}

/**
 *read_dir - opens and reads directory file names in search of fil
 *@er: 
 *
 *
 */
char *read_dir(char *er, struct dirent *s, char *fil, int l, char *fp, char *t)
{
	int i = 0;
	char *ret;

	for (i = 0; s->d_name[i] && fil[i]; i++)
	{
		if (s->d_name[i] != fil[i])
			break;
		if (i == (l - 1) && !(s->d_name[i + 1]))
		{
			ret = strcat(fp, "/");
			ret = strcat(ret, fil);
			free(t);
			return (ret);
		}
	}
	return (er);
}
/**
 *
 *
 *
 *
 */
char *save_path(char *tmp, char *path)
{
	int i = 0;

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
		return (tmp);
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
		return (path);
	}
	return ("error");
}
