#include "main.h"

void parseCommand(char *command, char **arg)
{
    int argIndex = 0;
    char *token = strtok(command, " \t\n\r");

    while (token != NULL && argIndex < MAX_ARGUMENTS - 1)
    {
        arg[argIndex] = token;
        token = strtok(NULL, " \t\n\r");
        argIndex++;
    }
    arg[argIndex] = NULL;
}

char* findCommandPath(const char* command) {
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
