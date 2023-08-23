#include "shell.h"

/**
 * main - entry function
 *
 * Return: 0 on success
 */
int main(void)
{
	char *cmd = NULL;
	int status = 0;
	size_t n = 0;

	for (;;)
	{
		if (isatty(STDIN_FILENO))
			_printf("$ ");
		if (_getline(&cmd, &n, STDIN_FILENO) == -1)
			free(cmd), exit(status);
		removeLeadingTrailingWhitespace(cmd);
		if (_strlen(_strdup(cmd)) == 0)
			continue;
		if (_strncmp(cmd, "exit", _strlen("exit")) == 0)
			break;
		else if (_strncmp(cmd, "env", 3) == 0)
			printEnv();
		status = executeCmd(cmd);
	}
	return (0);
}
