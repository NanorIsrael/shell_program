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

// typedef struct aliases {
//     char *alias_name;
//     char *real_name;
// } alias;

// alias **alias_db[] = { NULL, NULL };

typedef struct node {
    char *data;
    char *sub_data;
    struct node *next;
} l_node;

typedef struct global_data {
    char *file_name;
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];
    int   is_interactive;
    char **environ;
    l_node *alias_db;
    int number_of_args;
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
int alias_func(g_data *info);
int help_func(g_data *info);
int unalias_func(g_data *info);

// misc.d
char **init_g_data(g_data *info, char **av, char **env);
void free_all(g_data *);
ssize_t is_shell_interactive();
int parseline(const char *cmdline, char **argv);
char *path_finder(g_data *info);


// string helpers
int _strlen(char *s);
void _memcpy(void *dest, const void *src, unsigned int n);
char* sanitize_string(char* str);
char* sanitize_string2(char* str);
char* surround_with_quotes(const char* str);
int contains_quotes(const char* str);
// aliases.c
int set_alias(g_data *info);
int is_valid_alias(char *s);
l_node *find_alias(g_data *info, int idx);
void perform_alias_insert(g_data *info, char **data, char **sd);
// void check_alias(char *s);

// add_node.c
void insert_at_end(l_node **head, const char *str, const char *sub_data);

// linkedlist.c
void print_list(struct node *head);
void freeList(l_node **head);
void _prerror(char *e);
void _puts(const char *s);
void _putchar(char c);

// parser.c
char *find_command_path(const char * command);

// main
char *sh_read_line();