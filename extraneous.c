#include "shell.h"
/**
 * _strcmp - Compares two strings
 * @s1: First string
 * @s2: Second string
 * Return: Difference of first nonmatching character
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] == s2[i])
		{
			i++;
			continue;
		}
		else
		{
			return (s1[i] - s2[i]);
		}
	}
	return (0);
}
/**
 * prompt - prints $ for prompt
 * Return: void
 */
void prompt(void)
{
	write(1, "$ ", 3);
}
