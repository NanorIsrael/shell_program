#include "main.h"

char **init_g_data(g_data *info, char **av, char **env)
{
    int idx;
    // static char *array[MAX_COMMAND_LENGTH];
    // char **tempenv = array;

    info->file_name = av[0];
    info->is_interactive = 1;
    info->alias_db = NULL;
    // info->alias_db->next = NULL;
    // info->command = malloc(sizeof(1024));;

    for (idx = 0; env[idx]; idx++)
        ;

    info->environ = malloc(sizeof(char *) * (idx + 1));
    if (info->environ == NULL)
    {
        printf("failed to initialize envs");
        exit(0);
    }

    idx = 0;
    while (env[idx] != NULL)
    {
        info->environ[idx] = env[idx];
        idx++;
    }
   info->environ[idx] = NULL;

    // free(info->environ);
    
    return(NULL);
}