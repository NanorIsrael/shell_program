#include "main.h"

// typedef struct aliases {
//     char *alias_name;
//     char *real_name;
// } alias;

// alias alias_db[] = { NULL, NULL };

void check_alias(g_data *info, char *s)
{
    // l_node *temp = info->alias_db;

    // while (temp != NULL)
    // {
    //     printf("%s", alias_db[idx].alias_name);

    //     idx++;
    // }
}

int set_alias(g_data *info, char *str)
{
    // if (info->ar)
    char *r_name;
    l_node *ptr;

    r_name = strchr(str, '=');
    if(!r_name)
        return (1);
    // To Do: unset when !*+++p

    // call unset here

    insert_at_end(info, &(info->alias_db), str);

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