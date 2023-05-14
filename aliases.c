#include "main.h"

// #define MAX_ALIASES 100;
// typedef struct aliases {
//     char *alias_name;
//     char *real_name;
// } alias;

// alias alias_db[] = { NULL, NULL };
// const char **alias_commands[MAX_ALIASES];

void check_alias(g_data *info, char *s)
{
    // l_node *temp = info->alias_db;

    // while (temp != NULL)
    // {
    //     printf("%s", alias_db[idx].alias_name);

    //     idx++;
    // }
}

int set_alias(g_data *info)
{
    int idx = 1;
    // if (info->ar)
    char *token, *alias, *cmd, *arg_check;
    //  *ptr;
    while (info->arguments[idx] != NULL)
    {
        arg_check = strchr(info->arguments[idx], '=');
        if (!arg_check)
        {
            printf("sh: alias: %s: not found\n", info->arguments[idx]);
            idx++;
            continue;
        }

        token = strtok(info->arguments[idx], "=");
    
        while (token != NULL)
        {
            alias = token;
            token = strtok(NULL,  " \t\n");
            cmd = token;

            if (!cmd)
            {
                insert_at_end(info, &(info->alias_db), alias, NULL);
            }
            else
            {
                insert_at_end(info, &(info->alias_db), alias, cmd);
            }
            printf("%s = %s\n", alias, cmd);
            token = strtok(NULL, " \t\n");
        }
        idx++;
    }
    // if(!r_name)
    //     return (1);
    // To Do: unset when !*+++p

    // call unset here

    

    return (1);
}

int free_alias(g_data *info, const char *str)
{
    char *temp, ptr;
    int result;
    temp = strchr(str, '=');

    if(!temp)
        return (1);

    ptr = *temp;
    *temp = 0;
    // result = delete node here

    return (result);
}