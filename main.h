// i/o and parsing command libs
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// forking child process libs
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// stat
#include <sys/stat.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

typedef struct global_data {
    char *av;
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];
} g_data;


// parser.c
void parseCommand(char *command, char **arg);
ssize_t exec_cmd(g_data info, char *path);
void printPathDirectories();
char *_getenv(const char *name, char **_environ);
char* findCommandPath(const char* command);
int is_cmd(char *path);
