#include "shell.h"

/**
 * main - main function for the shell
 * @argc: number of arguments passed to main
 * @argv: array of arguments passed to main
 * @environment: array of environment variables
 *
 * Return: 0 or exit status, or ?
 */
int main(int argc, char **argv, char **environment)
{
	size_t buffer = 0;
	unsigned int interactive = 0, i, flag = 0;
	input_t inputs = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	UNUSED(argc);

	inputs.argv = argv;
	inputs.env = init_env(environment);
	signal(SIGINT, sig_handler);
	if (!isatty(STDIN_FILENO))
		interactive = 1;
	if (interactive == 0)
		_puts("$ ");
	flag = 0;
	while (getline(&(inputs.buffer), &buffer, stdin) != -1)
	{
		flag = 1;
		inputs.count++;
		inputs.commands = tokenize(inputs.buffer, ";");
		for (i = 0; inputs.commands && inputs.commands[i] != NULL; i++)
		{
			inputs.tokens = tokenize(inputs.commands[i], "\n \t\r");
			if (inputs.tokens && inputs.tokens[0])
				if (_builtins(&inputs) == NULL)
					check_path(&inputs);
			free(inputs.tokens);
		}
		free(inputs.buffer);
		free(inputs.commands);
		flag = 0;
		if (interactive == 0)
			_puts("$ ");
		inputs.buffer = NULL;
	}
	if (interactive == 0)
		_puts("\n");
	free_environ(inputs.env);
	free(inputs.buffer);
	exit(inputs.status);
}

/**
 * sig_handler - handles ^C signal interupt
 * @sig_handler: signal handler variable
 *
 * Return: void
 */
static void sig_handler(int sig_handler)
{
	unsigned int flag;
	(void) sig_handler;
	if (flag == 0)
		_puts("\n$ ");
	else
		_puts("\n");
}
