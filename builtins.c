#include "main.h"

const int PATH_MAX = 128;

int exit_func(g_data *info)
{
        char *u;
        int status;

        if (info->arguments[1] != NULL)
        {
            // Todo: check if is a valid digit
                 u = strtok(info->arguments[1] + 4, " ");
                status = atoi(u);
                exit(status);
        }
        else
        {
                // exit(0);
                //  free_all(g_data *info)
                //  free_all(info);

                return 0;
        }
    return (0);
}

int cd_func(g_data *info)
{
    char *d, *n, *c;
    if(info->arguments[1] == NULL)
    {
        d = getenv("HOME");
        if (d == NULL)
        {
            perror("cd");
            return(-1);
        }
    }
    else if (strcmp(info->arguments[1], "-") == 0)
    {
        d = getenv("OLDPWD");
        if (d == NULL)
        {
            perror("cd");
            return(-1);
        }
    }
    else
    {
        n = malloc(PATH_MAX);
        getcwd(n, PATH_MAX);
        setenv("OLDPWD", n, 1);
        free(n);
        if (chdir(info->arguments[1]))
        {
            // display similar error as sh
            perror("cd");
            return(-1);
        }
        c = malloc(PATH_MAX +5);
        getcwd(c, PATH_MAX);
        setenv("PWD", c, 1);
        free(c);
    }

    return(1);
}

int alias_func(g_data *info)
{
    char *alias;
    l_node *tmp;
    int idx = 1;

    if (info->arguments[1])
    {
        alias = strchr(info->arguments[1], '=');
        if (!alias)
        {
                while (info->arguments[idx] != NULL)
                {
                    tmp = find_alias(info, idx);
                    if (tmp)
                    {
                       print_alias(tmp);
                    }
                    else
                        error_handler(info, 127);
                    idx++;
                }
        }
        else
            set_alias(info);
    }
    else
    {
        tmp = info->alias_db;
        while (tmp != NULL)
        {
            print_alias(tmp);
            tmp = tmp->next;
        }
    }

    return (1);
}

int help_func(g_data *info)
{
    _puts("Simple Shell");
    _puts("builtin commands avaiable are:");
    _puts("exit - Used to exit the shell");
    _puts("cd - Used to change directory");
    _puts("help - Gives lists of command s available");
    _puts("setenv - Initialize a new environment variable");

    return (1);
}

int builtin_setenv(const char *a, const char *e)
{
    int i = 1;
    char *ev;
    if (a == NULL || e == NULL)
    {
        perror("setenv");
        return (-1);
    }
    ev = getenv(a);
    if (ev != NULL)
    {
        i = 1;
    }
    else
    {
        i = 0;
    }

    if (_setenv(a, e, i) != 0)
    {
        perror("setenv");
        return (-1);
    }

    return (0);
}

int _envp(void)
{
	char **env = environ;

	while (*env)
	{
		write(STDOUT_FILENO, *env, _strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
	return (0);
}

void print_alias(l_node *tmp)
{
    _print_one_line(tmp->data);
    _print_one_line("=");
    _print_one_line(tmp->sub_data);
    _putchar('\n');
}