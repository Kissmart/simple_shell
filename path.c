#include "shell.h"

/**
* findCommandInPath - find the path of the command
* @command: command to search for
* Return: full absolute path
*/

char *findCommandInPath(const char *command)
{
	char *path = _getenv("PATH"), *directory, *pathCopy;

	if (path == NULL)
	{
		_printf("Error: PATH environment variable not found.\n");
		return (NULL);
	}

	pathCopy = _strdup(path);
	if (pathCopy == NULL)
	{
		_printf("Error: Memory allocation failed.\n");
		return (NULL);
	}

	directory = _strtok(pathCopy, ":");
	while (directory != NULL)
	{
		int commandLen = _strlen(directory) + _strlen(command) + 2;
		char *fullCommandPath = (char *)malloc(commandLen * sizeof(char));

		if (fullCommandPath == NULL)
		{
			_printf("Error: Memory allocation failed.\n");
			free(pathCopy);
			return (NULL);
		}

		snprintf(fullCommandPath, commandLen, "%s/%s", directory, command);

		if (access(fullCommandPath, F_OK) == 0)
			return (_strdup(_strcat(directory, "/")));

		free(fullCommandPath);
		directory = _strtok(NULL, ":");
	}

	free(pathCopy);
	return (NULL);
}

/**
 * isAbsolutePath - Function to check if the command is an absolute path
 * @cmd: input string
 * Return: true if command is an absolute path, false otherwise
 */
bool isAbsolutePath(const char *cmd)
{
	if (cmd == NULL || _strlen(cmd) == 0)
		return (false);

	/* Check if it starts with a forward slash or Windows-style drive letter*/
	return (cmd[0] == '/' ||
	(_strlen(cmd) >= 3 && cmd[1] == ':' && cmd[2] == '/'));
}

/**
 * extractCommandFromPath - extract command from absolute path
 * @fullPath: Absolute Path
 * Return: Extracted command
*/
char *extractCommandFromPath(const char *fullPath)
{
	char *command = strrchr(fullPath, '/'); /* Find the last occurrence of '/'*/

	if (!command)
	{
		/* No '/' found in the path, return a copy of the fullPath*/
		return (_strdup(fullPath));
	}

	/* Increment the pointer to skip the '/'*/
	/* Allocate memory for the command name*/
	return (_strdup(++command));
}
