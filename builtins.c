#include "main.h"

int exit_func(g_data *info)
{
    // char *leak_test;
    // leak_test = malloc(sizeof(char *) *2);

    // leak_test++;
    printf("Hello world\n");
    // exit(0);
    return (-2);
}

int cd_func(g_data *info)
{
    // char *leak_test;
    // leak_test = malloc(sizeof(char));

    printf("Yet to implement change directory\n");
    return (0);
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

