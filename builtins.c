#include "main.h"

int exit_func(g_data *info)
{
        char *u;
        int status;

        u = strtok(info + 4, " ");
        if (u != NULL)
        {
                status = _atoi(u);
                exit(status);
        }
        else
        {
                exit(0);
        }
}

int cd_func(g_data *info)
{
    char *d, *n, *c;
    if(info->command == NULL)
    {
        d = getenv("HOME");
        if (d == NULL)
        {
            perror("cd");
            return(-1);
        }
    }
    else if (strcmp(info->command, "-")== 0)
    {
        d = getenv("OLDPWD");
        if (d == NULL)
        {
            perror("cd");
            return(-1);
        }
        _puts(d);
    }
    else
    {
        d = info->command;
    }

    n = malloc(PATH_MAX);
    getcwd(n, PATH_MAX);
    setenv("OLDPWD", n, 1);
    free(n);
    if (chdir(d == -1))
    {
        perror("chdir");
        return(-1);
    }
    c = malloc(PATH_MAX +5);
    getcwd(c, PATH_MAX);
    setenv("PWD", c, 1);
    free(c);
    return(0);
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
                        printf("%s=%s\n", tmp->data, tmp->sub_data);
                    else
                        printf("%s: alias: %s: not found\n", info->file_name, info->arguments[idx]);
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
            printf("%s=%s\n", tmp->data, tmp->sub_data);
            tmp = tmp->next;
        }
    }

    return (0);
}

void _help(g_data *info)
{
    _puts("Simple Shell");
    _puts("builtin commands avaiable are:");
    _puts("exit - Used to exit the shell");
    _puts("cd - Used to change directory");
    _puts("help - Gives lists of command s available");
    _puts("setenv - Initialize a new environment variable");
}

