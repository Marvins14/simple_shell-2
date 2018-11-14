#include "shell.h"

/**
 * _getenv - gets PATH from env
 * @env: env parameter
 * Return: PATH env
 */
int _getenv(char **env)
{
    int i;
    char *token;
    const char s[2] = ":";

    i = 0;
    while (env[i] != NULL)
    {
        if (_strcmp(env[i], "PATH") == 0)
                token = strtok(env[i], s);
        i++;
    }

    i = 0;
    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, s);
    }
    return (0);
}
