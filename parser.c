#include "main.h"

void parseCommand(g_data *info)
{
    int argIndex = 0, idx = 0;
    char *token, *rest, *alias_cmd;
    char *quote = "\"'";
    char *delim = " \t\n\r\a";
    l_node *alias;
    info->number_of_args = 0;
 
        if (_strchr(quote, info->command[0]))
        {
            alias = find_alias(info, 0);
            if(alias)
                _strcpy(info->command, alias->sub_data);
            
            rest = sanitize_string2(info->command);
            token = _sttrtok(rest, delim);
        }
        else
        {
            alias = find_alias(info, 0);

            if(alias)
                _strcpy(info->command, sanitize_string2(alias->sub_data));
            
            rest = info->command;
            token = _sttrtok(rest, delim);
        }

    while (token != NULL)
    {
        info->arguments[argIndex] = token;
        token = _sttrtok(NULL, delim);
        argIndex++;
        info->number_of_args++;
    }
    info->arguments[argIndex] = NULL; 
}

char* find_command_path(g_data *info, const char * command) 
{
    char* pathEnv = _getenv("PATH", info->environ); // Get the value of the PATH environment variable

    // Make a copy of pathEnv since strtok modifies the original string
    char* pathEnvCopy = strdup(pathEnv);

    // Tokenize the pathEnvCopy based on the ':' delimiter
    char* path = strtok(pathEnvCopy, ":");

    while (path != NULL) {
        char commandPath[1024];
        strcpy(commandPath, path);

        if (commandPath[strlen(commandPath) - 1] != '/')
            strcat(commandPath, "/");

        strcat(commandPath, command);

        // Check if the command exists at the current path
        if (access(commandPath, F_OK) == 0) {
            free(pathEnvCopy);
            return strdup(commandPath);
        }

        path = strtok(NULL, ":");
    }

    free(pathEnvCopy);
    return NULL; // Command not found in any path
}


char* sanitize_string(char* str) {
    int len = strlen(str);
    char* sanitized_str = malloc(len * 2 + 1); // Allocate enough space for worst case scenario (every character is a quote)
    if (sanitized_str == NULL) {
        _eputs("Error: Could not allocate memory for sanitized string.\n");
        return NULL;
    }
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == '\'' || str[i] == '\"' || str[i] == '\\') {
            // Escape the character
            sanitized_str[j++] = '\\';
        }
        sanitized_str[j++] = str[i];
    }
    sanitized_str[j] = '\0'; // Null-terminate the string
    return sanitized_str;
}

char *sanitize_string2(char* str) {
    int len = strlen(str);
    char sanitized_str[(len * 2) +1];
    
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == '\'' || str[i] == '\"' || str[i] == '\\') {
            // Escape the character
            // sanitized_str[j++] = '\\';
            continue;
        }
        sanitized_str[j++] = str[i];
    }
    sanitized_str[j] = '\0'; // Null-terminate the string

    return strdup(sanitized_str);
}