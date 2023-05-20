#include "main.h"


int unalias_func(g_data *info)
{
    l_node *tmp, *prev;
    int idx = 1, result = 0;

    if (info->arguments[1])
    {
        tmp = info->alias_db;

        while (info->arguments[idx] != NULL)
        {
            while (tmp != NULL)
            {
                prev = tmp;
                if (strcmp(info->arguments[idx], tmp->data) == 0)
                {
                    prev->next = tmp->next;
                    // tmp = prev
                    free(tmp->data);
                    free(tmp->sub_data);
                    // free(tmp);
                    break;
                }
                tmp = tmp->next;
            }
            idx++;
        }
    }
    else{
        printf("unalias: usage: unalias [-a] name [name ...]\n");
        // return (0);
    }
 
    return (1);
}

int set_alias(g_data *info)
{
    int idx = 1, excess_count = 0;
    char *token, *alias, *cmd, *arg_check, *temp;
    char *ensure_full_alias[100], *token_copy;

    // info->arguments[info->number_of_args - 1] = NULL;
    while (idx <= info->number_of_args && info->arguments[idx] != NULL)
    {
     
        if (contains_quotes(strdup(info->arguments[idx])))
        {
            token_copy = malloc(sizeof(char *) * 1024);
                strcpy(token_copy, info->arguments[idx]);
                    idx++;
                    while (info->arguments[idx] != NULL) {
                        strcat(token_copy, " ");
                        strcat(token_copy, info->arguments[idx]);

                        if((strchr(info->arguments[idx], '\'')) || (strchr(info->arguments[idx], '\"')))
                            break;

                        idx++;
                    }
                    token = strtok(token_copy, "=");
                    free(token_copy);
        }
        else
        {
            if (is_valid_alias(info->arguments[idx]))
                token =  strtok(info->arguments[idx], "=");
            else
            {
                idx++;
                continue;
            }
               
        }

        while (token != NULL)
        {
            ensure_full_alias[excess_count] = token;
            excess_count++;
            token= strtok(NULL, " \t\n");
        }
        ensure_full_alias[excess_count] = NULL;

        temp = malloc(sizeof(char *) * 32);
        if (temp == NULL)
        {
            free(temp);
            return (0);
        }
        cmd = temp;
        for (int j= 0; j < excess_count - 1; j++)
        {
            alias = strdup(ensure_full_alias[j]);
            j++;
            if (strlen(ensure_full_alias[j]) > 0 && contains_quotes(ensure_full_alias[j]))
            {
                strcpy(cmd, strdup(ensure_full_alias[j]));
                j++;
                while(j < excess_count)
                {
                    strcat(cmd, " ");
                    strcat(cmd, strdup(ensure_full_alias[j]));
                    j++;
                }
                cmd = surround_with_quotes(sanitize_string2(cmd));
            }
            else
            {
                cmd = strlen(ensure_full_alias[j]) > 0 ? 
                surround_with_quotes(strdup(ensure_full_alias[j])) 
                : NULL;
            }
        }
            if (!cmd)
                {
                    perform_alias_insert(info, &alias, NULL);
                // insert_at_end(&(info->alias_db), alias, NULL);
                }
            else
            {
                 perform_alias_insert(info, &alias, &cmd);
            }

        excess_count = 0;
        idx++;

        free(cmd);
        free(temp);
    }
    return (1);
}

int free_alias(const char *str)
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

char* surround_with_quotes(const char* str) {
    size_t len = strlen(str);
    char* quoted_str = malloc(len + 3); // Allocate memory for the quoted string

    if (quoted_str == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for quoted string.\n");
        return NULL;
    }

    // Add the opening quote
    quoted_str[0] = '\'';
    
    // Copy the original string
    strncpy(quoted_str + 1, str, len);

    // Add the closing quote
    quoted_str[len + 1] = '\'';
    quoted_str[len + 2] = '\0';

    return quoted_str;
}

int contains_quotes(const char* str) {
    return (strchr(str, '\"') != NULL) || (strchr(str, '\'') != NULL);
}

int is_valid_alias(char *s)
{
    char *arg_check;

    arg_check = strchr(s, '=');
    if (!arg_check)
    {
        printf("sh: alias: %s: not found\n", s);
        return (0);
    }

    return (1);
}

l_node *find_alias(g_data *info, int idx)
{
    l_node *tmp;

        tmp = info->alias_db;
        while (tmp != NULL)
        {
            if (strcmp(info->arguments[idx], tmp->data) == 0)
            {
                return tmp;
            }
            tmp = tmp->next;
        }

    return (NULL);
}

void perform_alias_insert(g_data *info, char **data, char **sd)
{
    l_node *tmp;

        tmp = info->alias_db;
        if (tmp != NULL)
        {
            while (tmp != NULL)
            {
                if (strcmp(*data, tmp->data) == 0)
                {
                        tmp->data = *data;
                        tmp->sub_data = *sd ? *sd : "'\'\'";
                        break;
                }
                else if(tmp->next == NULL)
                {                    
                    insert_at_end(&(info->alias_db), strdup(*data), strdup(*sd));
                }
               
                tmp = tmp->next;
            }
        }
        else
        {
            insert_at_end(&(info->alias_db), strdup(*data), strdup(*sd));
        }

        // free(*data);
        // free(*sd);
}