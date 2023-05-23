#include "main.h"

char **init_g_data(g_data *info, char **av, char **env, int c)
{
    int idx;

    info->file_name = av[0];
    info->file = av[1];
    info->number_of_args = 0;
    info->counter = 1;
    info->readfd = 0;
    info->argc = c;
    info->alias_db = NULL;
    // info->alias_db->next = NULL;
    // info->command = malloc(sizeof(1024));;

    for (idx = 0; env[idx]; idx++)
        ;

    info->environ = malloc(sizeof(char *) * (idx + 1));
    if (info->environ == NULL)
    {
        _puts("failed to initialize envs");
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

        tokens = _sttrtok(NULL,  " \t\n\r\a");
        idx++;
    }
    command[idx] = ";";
    command[idx + 1] = NULL;

   g_cmd = malloc(sizeof(char *) *idx + 10);
   _strcpy(g_cmd, "\"");

    int j=0, m=0;
    while (command[j] != NULL)
    {

         if ( _strcmp(command[j], ";") == 0)
            {
                _strcat(g_cmd, "\"");
                fcommand[m] = _strdup(g_cmd);
                m++;
                _strcpy(g_cmd, "\"");
            }
            else 
            {
                _strcat(g_cmd, command[j]);
                _strcat(g_cmd, " ");
            }
            j++;
    }
    fcommand[m] = NULL;
    free(g_cmd);
}

ssize_t is_shell_interactive()
{
    return isatty(STDIN_FILENO);
}


void free_all(g_data *info)
{

    free(info->environ);
    freeList(&(info->alias_db));
    // free(info->arguments);
}