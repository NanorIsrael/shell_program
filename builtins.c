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

    if (info->arguments[1])
    {
        alias = strchr(info->arguments[1], '=');
        if (!alias)
            return (0);

        // printf("%s", alias);
        set_alias(info);
        //  print_list(info->alias_db);
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
    //  printf("Yet to implement %s\n", info->arguments[1]);

    // info->alias_db(info->alias_db);

    //  check_alias("");
    return (0);
}