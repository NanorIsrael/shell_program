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
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements");
		return (0);
	}
	if (_setenv(info->arguments[1], info->arguments[2], 1))
		return (1);
	return (1);
}

// /**
//  * unsetenv_func - Remove an environment variable
//  * @info: Structure containing potential arguments. Used to maintain
//  *        constant function prototype.
//  *  Return: Always 0
//  */
// int unsetenv_func(g_data *info)
// {
// 	int i;

// 	if (info->argc == 1)
// 	{
// 		_eputs("Too few arguements.");
// 		return (0);
// 	}
// 	for (i = 1; i <= info->argc; i++)
// 		_unsetenv(info, info->arguments[i]);

// 	return (1);
// }

// /**
//  * _unsetenv - Remove an environment variable
//  * @info: Structure containing potential arguments. Used to maintain
//  *        constant function prototype.
//  *  Return: 1 on delete, 0 otherwise
//  * @var: the string env var property
//  */
// int _unsetenv(g_data *info, char *var)
// {
// 	list_t *node = info->env;
// 	size_t i = 0;
// 	char *p;

// 	if (!node || !var)
// 		return (0);

// 	while (node)
// 	{
// 		p = starts_with(node->str, var);
// 		if (p && *p == '=')
// 		{
// 			info->env_changed = delete_node_at_index(&(info->env), i);
// 			i = 0;
// 			node = info->env;
// 			continue;
// 		}
// 		node = node->next;
// 		i++;
// 	}
// 	return (info->env_changed);
// }

// /**
//  * _setenv - Initialize a new environment variable,
//  *             or modify an existing one
//  * @info: Structure containing potential arguments. Used to maintain
//  *        constant function prototype.
//  * @var: the string env var property
//  * @value: the string env var value
//  *  Return: Always 0
//  */
// // int _setenv(info_t *info, char *var, char *value)
// {
// 	char *buf = NULL;
// 	list_t *node;
// 	char *p;

// 	if (!var || !value)
// 		return (0);

// 	buf = malloc(_strlen(var) + _strlen(value) + 2);
// 	if (!buf)
// 		return (1);
// 	_strcpy(buf, var);
// 	_strcat(buf, "=");
// 	_strcat(buf, value);
// 	node = info->env;
// 	while (node)
// 	{
// 		p = starts_with(node->str, var);
// 		if (p && *p == '=')
// 		{
// 			free(node->str);
// 			node->str = buf;
// 			info->env_changed = 1;
// 			return (0);
// 		}
// 		node = node->next;
// 	}
// 	add_node_end(&(info->env), buf, 0);
// 	free(buf);
// 	info->env_changed = 1;
// 	return (0);
// }

int _setenv(const char *n, const char *val, int w)
    {
         char *buffer, **env = environ;
        size_t nlen = strlen(n),  vallen = strlen(val), bufferLen;
    
    if (n == NULL || n[0] == '\0' || strchr(n, '=') != NULL || val == NULL)
    {
        return (-1);
    }

    if (!w && getenv(n) != NULL)
     {
         return (0);
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
    return (0);
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

       return (0);
}

