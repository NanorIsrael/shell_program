#include "main.h"

/**
 * setenv_func - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int setenv_func(g_data *info)
{
	if (info->number_of_args != 3)
	{
		_eputs("Incorrect number of arguements");
		return (0);
	}
	if (_setenv(info->arguments[1], info->arguments[2], 1))
		return (1);
	return (1);
}

/**
 * unsetenv_func - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int unsetenv_func(g_data *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.");
		return (0);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->arguments[i]);

	return (1);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(g_data *info, char *var)
{
	// list_t *node = info->env;
	size_t i = 0;
	ssize_t p;
    char **env_list;

	if (!var)
		return (0);

	while (info->environ[i] != NULL)
	{
        env_list[i] = info->environ[i];

		p = _strncmp(info->environ[i], var, _strlen(var));
		if (p)
		{
			continue;
		}
		i++;
	}
    env_list[i] = NULL;

    i = 0;
    while (env_list[i] != NULL)
	{
        info->environ[i] = env_list[i];
		i++;
	}

	return (1);
}


int _setenv(const char *n, const char *val, int w)
    {
         char *buffer, **env = environ;
        size_t nlen = strlen(n),  vallen = strlen(val), bufferLen;
    
    if (n == NULL || n[0] == '\0' || strchr(n, '=') != NULL || val == NULL)
    {
        return (-1);
    }

    bufferLen= nlen + vallen + 2;
    buffer = (char *) malloc(bufferLen);

    if (buffer == NULL)
    {
        return (-1);
    }
    strcpy(buffer, n);
    strcat(buffer, "=");
    strcat(buffer, val);
    while (*env != NULL)
     {
        if (strncmp(*env, n, nlen) == 0 && (*env)[nlen] == '=')
        {
            if (w)
             {
              *env = buffer;
                //free(*env);
            }
            else
             {
              free(buffer);
              return (0);
            }
            break;
        }
        env++;
    }
     free(buffer);
    return (1);
}

int _existadd(char **env, char *buffer)
{
    size_t elen = 0;
    char **n;
    if (*env == NULL)
    {
        while (environ[elen] != NULL)
        {
                elen++;
        }
        n = (char **) malloc((elen + 2) * sizeof(char *));
        if (n == NULL) {
            free(buffer);
            return (-1);
        }
        environ = n;
        environ[elen] = buffer;
        environ[elen + 1] = NULL;
        free(n);
        }

       return (1);
}

