#include "main.h"

void parseCommand(g_data *info)
{
    int argIndex = 0, idx = 0;
    char *token, *rest, *alias_cmd;
    char *quote = "\"'";
    char *delim = " \t\n\r\a";
    l_node *alias;
    info->number_of_args = 0;
    // const char *dupstr = strdup(info->command);
    // if ((strcmp(info->command[0], "")) == 0)
    //     reti;
        if (strchr(quote, info->command[0]))
        {
            alias = find_alias(info, 0);
            if(alias)
                strcpy(info->command, alias->sub_data);
            
            rest = sanitize_string2(info->command);
            token = strtok(rest, delim);
        }
        else
        {
            alias = find_alias(info, 0);
            // printf("the subdata%s\n", alias->data);

            if(alias)
                strcpy(info->command, sanitize_string2(alias->sub_data));
            
            rest = info->command;
            token = strtok(rest, delim);

            // free(rest);
        }

    while (token != NULL)
    {
        info->arguments[argIndex] = token;
        token = strtok(NULL, delim);
        argIndex++;
        info->number_of_args++;
    }
    info->arguments[argIndex] = NULL; 

    // printf("I love debugging\n");
}

char* find_command_path(const char * command) 
{
    char* pathEnv = getenv("PATH"); // Get the value of the PATH environment variable

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

void printPathDirectories(char **environ) 
{
    char* path = 
    // _getenv("PATH", environ);

     getenv("PATH");
    if (path == NULL) {
        printf("PATH environment variable not set.\n");
        return;
    }

    char* pathCopy = strdup(path);
    if (pathCopy == NULL) {
        perror("strdup");
        return;
    }

    char* token = strtok(pathCopy, ":");
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ":");
    }

    free(pathCopy);
}


/* 
 * parseline - Parse the command line and build the argv array.
 * 
 * Characters enclosed in single quotes are treated as a single
 * argument.  Return true if the user has requested a BG job, false if
 * the user has requested a FG job.  
 */
int parseline(const char *cmdline, char **argv) 
{
    static char array[MAX_COMMAND_LENGTH]; /* holds local copy of command line */
    char *buf = array;          /* ptr that traverses command line */
    char *delim;                /* points to first space delimiter */
    int argc;                   /* number of args */
    int bg;                     /* background job? */

    strcpy(buf, cmdline);
    buf[strlen(buf)-1] = ' ';  /* replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* ignore leading spaces */
	buf++;

    /* Build the argv list */
    argc = 0;
    if (*buf == '\'') {
	buf++;
	delim = strchr(buf, '\'');
    }
    else {
	delim = strchr(buf, ' ');
    }

    while (delim) {
        printf("this is it ========%s\n", buf);

	argv[argc++] = buf;
	*delim = '\0';
	buf = delim + 1;
	while (*buf && (*buf == ' ')) /* ignore spaces */
	       buf++;

	if (*buf == '\'') {
	    buf++;
	    delim = strchr(buf, '\'');
	}
	else {
	    delim = strchr(buf, ' ');
	}
    }
    argv[argc] = NULL;
    
    if (argc == 0)  /* ignore blank line */
	return 1;

    /* should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0) {
	argv[--argc] = NULL;
    }
    return bg;
}

char* sanitize_string(char* str) {
    int len = strlen(str);
    char* sanitized_str = malloc(len * 2 + 1); // Allocate enough space for worst case scenario (every character is a quote)
    if (sanitized_str == NULL) {
        fprintf(stderr, "Error: Could not allocate memory for sanitized string.\n");
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