#include "main.h"

// void print_error(g_data *info, char *estr)
// {
// 	puts(info->av[0]);
// 	puts(": ");
// 	print_d(info->line_count, STDERR_FILENO);
// 	puts(": ");
// 	puts(info->arguments[0]);
// 	puts(": ");g
// 	puts(estr);
// }

/**
 * error_not_found - generic error message for command not found
 * @datash: data relevant (counter, arguments)
 * Return: Error message
 */
void p_error(g_data *info)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = "haibo";
    // aux_itoa(datash->counter);
	length = strlen(info->file_name) + strlen(ver_str);
	length += strlen(info->arguments[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		// free(ver_str);
		// return (NULL);
	}
	strcpy(error, info->file_name);
	strcat(error, ": ");
	strcat(error, ver_str);
	strcat(error, ": ");
	strcat(error, info->arguments[0]);
	strcat(error, ": not found\n");
	strcat(error, "\0");
	// free(ver_str);
	write(STDERR_FILENO, error, strlen(error));
		free(error);
}

int main(int ac __attribute__((unused)), char **av, char **env)
{
    g_data info;

    ac++;
    // *av++;

    // info.file_name = av[0];

    // To Do:
    // function to set_data(info)
    init_g_data(&info, av, env);
    cmd_handler(&info);

    printf("Continuing my normal execution flow\n");
    // free_all(&info);
    // atexit(report_mem_leak);
}

ssize_t exec_cmd(g_data *info, char *path)
{
    int status;

    const int pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        execve(path, info->arguments, info->environ);
        // execvp(path, info.arguments);

        perror(info->file_name);
        exit(EXIT_FAILURE);
    }
    else {
        wait(&status);
        // check waitpid

        if (WIFEXITED(status))
        {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("Child process terminated abnormally\n");
        }
    }

    return (1);
}

/**
 * is_cmd - determines if a file is an executable command
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(char *path)
{
	struct stat st;

	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

ssize_t handle_builtins(g_data *info)
{
    int idx, result = -1;
    csh_builtin cbuiltins[] = {
        {"exit", exit_func},
        {"cd", cd_func},
        {"alias", alias_func},
        {NULL, NULL}
    };

        // printf("this is commmand %s\n", info->command);
        // printf("this is arg 0 %s\n", info->arguments[0]);
    if (info->arguments[0])
    {
        for (idx = 0; cbuiltins[idx].name; idx++)
        {
            if (strcmp(cbuiltins[idx].name, info->arguments[0]) == 0)
            {
                if (strcmp(cbuiltins[idx].name, info->arguments[0]) == 0)
                {
                    // todo some counter
                    result = cbuiltins[idx].handler(info);
                    break;
                }
            }
        }
    } 
    return (result);
}

void cmd_handler(g_data *info)
{
    int str_size, i = 0, ret = 1, debugger= 0; 

    while (ret == 1 && info->is_interactive)
    {
        info->is_interactive = is_shell_interactive();
        if (info->is_interactive == 1)
        {
            write(STDOUT_FILENO, "$ " , 2);
            fflush(stdout);
        }

        fflush(stdin);
        // fgets((info->command), sizeof(info->command), stdin);
    //    if (strcmp(sh_read_line(), ""));
        
        strcpy(info->command, sh_read_line());


        // if(strlen(info->command) > 0)
        // {
            str_size = strlen(info->command);
            if ( str_size > 0 && info->command[str_size - 1] == '\n') {
            info->command[str_size - 1] = '\0';
        }
        parseCommand(info);

        // // implement builtins here
        ret = handle_builtins(info);

        if (ret == -1) 
        {    
            if (strlen(info->command) == 0) 
            {
                ret = 1;
                continue;
            }
            
            char *commandPath = find_command_path(info->command);

            if (commandPath != NULL) {
                printf("Command path: %s\n", commandPath);
                ret = exec_cmd(info, commandPath);
                
                free(commandPath);
            }
            else {
                    if (info->arguments[0][0] == '/' && is_cmd(info->arguments[0]) == 1)
                    {
                        ret = exec_cmd(info, info->arguments[0]);
                        free(commandPath);
                    }
                    else
                    {
                        // check if is an alias and execute here
                        p_error(info);
                        ret = 1;
                    }   
            }
        }

        // if (is_shell_interactive() != 0)
        // {
        //    printf("Shell is interactive \n");
        //    putchar('\n');

        // }

    }
    printf("Enter a command to %d\n", ret);

    free_all(info);
    atexit(report_mem_leak);
}



void free_all(g_data *info)
{

    free(info->environ);
    freeList(&(info->alias_db));
    // free(info->arguments);
}

ssize_t is_shell_interactive()
{
    return isatty(STDIN_FILENO);
}

// char *path_finder(g_data *info)
// {
//     l_node *alias;
//     char *cmd;

//     // alias = find_alias(info, 0);

//     // if(alias)
//     //     cmd = (sanitize_string2(alias->sub_data));
//     // else
//     //     cmd = info->command;

//     printf("the command %s\n", cmd);
//     return ());
// }

char* sh_read_line() {
    char *line = NULL;
    size_t buflen = 0;

    if (getline(&line, &buflen, stdin) == -1)
    {
        if (feof(stdin))
        {
            perror("getline");
            exit(EXIT_SUCCESS);
        }
        else
        {
            exit(EXIT_FAILURE);
        }
    }
    return line;
}
