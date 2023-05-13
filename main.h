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

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 128

typedef struct global_data {
    char *file_name;
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];
    int   is_interactive;
    char **environ;
} g_data;

typedef struct builtins {
    char *name;
    int (*handler)(g_data *);
} csh_builtin;


// parser.c
void parseCommand(g_data *info);
char* findCommandPath(const char *command);
void printPathDirectories();

int is_cmd(char *path);
void cmd_handler(g_data *info);


char *_getenv(const char *name, char **_environ);


// builtins
int exit_func(g_data *info);
int cd_func(g_data *info);

// misc.d
char **init_g_data(g_data *info, char **av, char **env);
void free_all(g_data *);
ssize_t is_shell_interactive();
int parseline(const char *cmdline, char **argv);
