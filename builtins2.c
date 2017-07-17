#include "shell.h"

/**
 * add_key - create a new environment variable
 * @vars: pointer to struct of variables
 *
 * Return: void
 */
void add_key(vars_t *vars)
{
	unsigned int i;
	char **newenv;

	for (i = 0; vars->env[i] != NULL; i++)
		;
	newenv = malloc(sizeof(char *) * (i + 2));
	if (newenv == NULL)
	{
		print_error(vars, NULL);
		vars->status = 127;
		new_exit(vars);
	}
	for (i = 0; vars->env[i] != NULL; i++)
		newenv[i] = vars->env[i];
	newenv[i] = add_value(vars);
	if (newenv[i] == NULL)
	{
		free(newenv);
		exit(1);
	}
	newenv[i + 1] = NULL;
	free(vars->env);
	vars->env = newenv;
}

/**
 * find_key - finds an environment variable
 * @env: array of environment variables
 * @key: environment variable to find
 *
 * Return: pointer to address of the environment variable
 */
char **find_key(char **env, char *key)
{
	unsigned int i, j, len;

	len = _strlen(key);
	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; j < len; j++)
			if (key[j] != env[i][j])
				break;
		if (j == len && env[i][j] == '=')
			return (&env[i]);
	}
	return (NULL);
}

/**
 * add_value - create a new environment variable string
 * @vars: pointer to struct of variables
 *
 * Return: pointer to the new string;
 */
char *add_value(vars_t *vars)
{
	unsigned int len1, len2, i, j;
	char *new;

	len1 = _strlen(vars->av[1]);
	len2 = _strlen(vars->av[2]);
	new = malloc(sizeof(char) * (len1 + len2 + 2));
	if (new == NULL)
	{
		free(vars->buffer);
		free(vars->av);
		free_env(vars->env);
		return (NULL);
	}
	for (i = 0; vars->av[1][i] != '\0'; i++)
		new[i] = vars->av[1][i];
	new[i] = '=';
	for (j = 0; vars->av[2][j] != '\0'; j++)
		new[i + 1 + j] = vars->av[2][j];
	new[i + 1 + j] = '\0';
	return (new);
}

/**
 * _atoi - converts a string into an integer
 * @str: string to convert
 *
 * Return: the integer value, or -1 if an error occurs
 */
int _atoi(char *str)
{
	unsigned int i, digits;
	int num = 0, num_test;

	num_test = INT_MAX;
	for (digits = 0; num_test != 0; digits++)
		num_test /= 10;
	for (i = 0; str[i] != '\0' && i < digits; i++)
	{
		num *= 10;
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		if ((i == digits - 1) && (str[i] - '0' > INT_MAX % 10))
			return (-1);
		num += str[i] - '0';
		if ((i == digits - 2) && (str[i + 1] != '\0') && (num > INT_MAX / 10))
			return (-1);
	}
	if (i > digits)
		return (-1);
	printf("%d\n", num);
	return (num);
}
