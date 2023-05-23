#include "main.h"

int error_handler(g_data *info, int err_val)
{
    char *er_str;

    switch(err_val)
    {
        case -1:
            er_str = env_err(info);
            break;
        case 2:
            if (_strcmp("exit", info->arguments[0]) == 0)
            er_str = exit_shell_err(info);
            else
            er_str = get_cd_error(info)
;
        case 126:
            er_str = path_126_err(info);
            break;
        case 127:
            er_str = not_found_err(info);
    }

	if (er_str)
	{
		write(STDERR_FILENO, er_str, _strlen(er_str));
		free(er_str);
	}

    return (err_val);
}

ssize_t handle_builtins(g_data *info)
{
    int idx, result = -1;
    csh_builtin cbuiltins[] = {
        {"exit", exit_func},
        {"cd", cd_func},
        {"env", _envp},
        {"setenv", setenv_func},
        {"unsetenv", unsetenv_func},
        {"alias", alias_func},
        {"unalias", unalias_func},
        {"help", help_func},
        {NULL, NULL}
    };

    if (info->arguments[0])
    {
        for (idx = 0; cbuiltins[idx].name; idx++)
        {
            if (_strcmp(cbuiltins[idx].name, info->arguments[0]) == 0)
            {
                if (_strcmp(cbuiltins[idx].name, info->arguments[0]) == 0)
                {
                    // todo some counter
                    result = cbuiltins[idx].handler(info);
                    break;
                }
            }
        }
    } 
    return (result);
}

/**
 * _strncmp - compares length of a string
 * @s: string to compare
 * @t: string to compare
 * Return: Always zero
 */

int _strncmp(const char *s, const char *t, size_t len)
{
    int i = 0; 
	while ((*s && (*s == *t)) && i < len)
	{
		++s;
		++t;
        i++;
	}
	return (*(const unsigned char *)s - *(const unsigned char *)t);
}