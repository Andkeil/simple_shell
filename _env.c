#include "shell.h"

/**
 *
 *
 *
 *
 *
 */
char **init_env(char **environ)
{
	char **new = NULL;
	size_t n = 0;

	for (; environ[n] != NULL; n++)
		;
	new = malloc(sizeof(char *) * (n + 1));
	if (new == NULL)
	{
		perror("Uncharted territory");
		exit(1);

	}
	for (n = 0; environ[n] ! = NULL; n++)
		new[n] = _strdup(environ[n]);
	new[n] = NULL;
	return (new);
}

void free_environ(char **environ)
{
	unsigned int n;

	for (n = 0; environ[n] != NULL; n++)
		free(environ[n]);
	free(environ);
}
