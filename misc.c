#include "main.h"

char **init_g_data(g_data *info, char **av, char **env)
{
    int idx;
    // static char *array[MAX_COMMAND_LENGTH];
    // char **tempenv = array;

    info->file_name = av[0];
    info->is_interactive = 1;
    info->number_of_args = 0;
    info->counter = 1;
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

void semi_colon_hanler(char *input, char *tokens, char **fcommand)
{
    char *command[20];
   
    char *g_cmd, *ptr;
    int idx=0;

     while (tokens != NULL)
    {
        command[idx] = tokens;

        tokens = strtok(NULL,  " \t\n\r\a");
        idx++;
    }
    command[idx] = ";";
    command[idx + 1] = NULL;

   g_cmd = malloc(sizeof(char *) *idx + 10);
   strcpy(g_cmd, "\"");

    int j=0, m=0;
    while (command[j] != NULL)
    {

         if ( strcmp(command[j], ";") == 0)
            {
                strcat(g_cmd, "\"");
                fcommand[m] = strdup(g_cmd);
                m++;
                strcpy(g_cmd, "\"");
            }
            else 
            {
                strcat(g_cmd, command[j]);
                strcat(g_cmd, " ");
            }
            j++;
    }
    fcommand[m] = NULL;

     
    free(g_cmd);
    // return fcommand;
}