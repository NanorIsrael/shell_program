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

// leak detector
#include "leak_detector_c.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

typedef struct global_data {
    char *file_name;
    char *command;
    char *arguments;
} g_data;

typedef struct builtins {
    char *name;
    int (*handler)(g_data *);
} csh_builtin;


// parser.c
void parseCommand(char *command, char **arg);
char* findCommandPath(const char* command);
void printPathDirectories();

int is_cmd(char *path);
void cmd_handler(g_data *info);


char *_getenv(const char *name, char **_environ);


// builtins
int exit_func();