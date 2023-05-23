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
                if (_strcmp(info->arguments[idx], tmp->data) == 0)
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
        _puts("unalias: usage: unalias [-a] name [name ...]");
        // return (0);
    }
 
    return (1);
}

int set_alias(g_data *info)
{
    int idx = 1, excess_count = 0;
    char *token, *arg_check, *ensure_full_alias[100], *token_copy;
    char **ptr;

    while (idx <= info->number_of_args && info->arguments[idx] != NULL)
    {
     
        if (contains_quotes(_strdup(info->arguments[idx])))
        {
           token_copier(info, &token, &idx);
        }
        else
        {
            if (is_valid_alias(info, info->arguments[idx]))
                token =  _sttrtok(info->arguments[idx], "=");
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
            token= _sttrtok(NULL, " \t\n");
        }
        ensure_full_alias[excess_count] = NULL;
        ptr = ensure_full_alias;
        process_alias(info, &ptr, &excess_count);
        excess_count = 0;
        idx++;     
    }
    return (1);
}

void process_alias(g_data *info, char ***aliases, int *excess_count)
{
        int j;
        char *alias, *temp, *cmd;

        temp = malloc(sizeof(char *) * 32);
        if (temp == NULL)
        {
            free(temp);
            return;
        }
        cmd = temp;
        for (j= 0; j < *excess_count - 1; j++)
        {
            alias = _strdup((*aliases)[j]);
            j++;
            if (_strlen((*aliases)[j]) > 0 && contains_quotes((*aliases)[j]))
            {
                _strcpy(cmd, _strdup((*aliases)[j]));
                j++;
                while(j < *excess_count)
                {
                    _strcat(cmd, " ");
                    _strcat(cmd, _strdup((*aliases)[j]));
                    j++;
                }
                cmd = surround_with_quotes(sanitize_string2(cmd));
            }
            else
            {
                cmd = _strlen((*aliases)[j]) > 0 ? surround_with_quotes(_strdup((*aliases)[j])) 
                : NULL;
            }
        }
            if (!cmd)
                perform_alias_insert(info, &alias, NULL);
            else
                perform_alias_insert(info, &alias, &(cmd));
        free(cmd);
        free(temp);
}


int free_alias(const char *str)
{
    char *temp, ptr;
    int result;
    temp = _strchr(str, '=');

    if(!temp)
        return (1);

    ptr = *temp;
    *temp = 0;
    // result = delete node here

    return (result);
}

char* surround_with_quotes(char* str) {
    size_t len = _strlen(str);
    char* quoted_str = malloc(len + 3); // Allocate memory for the quoted string

    if (quoted_str == NULL) {
        _eputs("Error: Could not allocate memory for quoted string.");
        return NULL;
    }

    // Add the opening quote
    quoted_str[0] = '\'';
    
    // Copy the original string
    _strncpy(quoted_str + 1, str, len);

    // Add the closing quote
    quoted_str[len + 1] = '\'';
    quoted_str[len + 2] = '\0';

    return quoted_str;
}

int contains_quotes(const char* str) {
    return (_strchr(str, '\"') != NULL) || (_strchr(str, '\'') != NULL);
}

int is_valid_alias(g_data *info, char *s)
{
    char *arg_check;

    arg_check = _strchr(s, '=');
    if (!arg_check)
    {
        error_handler(info, 127);
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
            if (_strcmp(info->arguments[idx], tmp->data) == 0)
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
                if (_strcmp(*data, tmp->data) == 0)
                {
                        tmp->data = *data;
                        tmp->sub_data = *sd ? *sd : "'\'\'";
                        break;
                }
                else if(tmp->next == NULL)
                {                    
                    insert_at_end(&(info->alias_db), _strdup(*data), _strdup(*sd));
                }
               
                tmp = tmp->next;
            }
        }
        else
        {
            insert_at_end(&(info->alias_db), _strdup(*data), _strdup(*sd));
        }

        // free(*data);
        // free(*sd);
}

int token_copier(g_data *info, char **token, int *idx)
{
    char *token_copy;

    token_copy = malloc(sizeof(char *) * 1024);
    if (!token_copy)
    {
        free(token_copy);
        return (0);
    }
    _strcpy(token_copy, info->arguments[*idx]);
    (*idx)++;
    while (info->arguments[*idx] != NULL) 
    {
        _strcat(token_copy, " ");
        _strcat(token_copy, info->arguments[*idx]);

        if((_strchr(info->arguments[*idx], '\'')) || (_strchr(info->arguments[*idx], '\"')))
            break;

           (*idx)++;
    }
    *token = _sttrtok(token_copy, "=");
    free(token_copy);

    return (*idx);
}
