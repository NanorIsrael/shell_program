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
    if (info->arguments[1])
    {
        set_alias(info, info->arguments[1]);
        //  print_list(info->alias_db);
    }
    else
    {
        print_list(info->alias_db);
    }
    //  printf("Yet to implement %s\n", info->arguments[1]);

    // info->alias_db(info->alias_db);

    //  check_alias("");
    return (0);
}