#include "main.h"

// void print_error(g_data *info, char *estr)
// {
// 	puts(info->av[0]);
// 	puts(": ");
// 	print_d(info->line_count, STDERR_FILENO);
// 	puts(": ");
// 	puts(info->arguments[0]);
// 	puts(": ");
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

int main(int ac, char **av, char **env)
{
    g_data info;

    ac++;
    // *av++;

    info.file_name = av[0];

    // To Do:
    // function to set_data(info)

    cmd_handler(&info);

    printf("Continuing my normal execution flow\n");
    atexit(report_mem_leak);
}

ssize_t exec_cmd(g_data *info, char *path)
{
    int status;

    const int pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
        return (-1);
    }
    else if (pid == 0)
    {
        execve(path, info->arguments, NULL);
        // execvp(path, info.arguments);

        perror(info->file_name);
        exit(EXIT_FAILURE);
        return (-1);
    }
    else {
        wait(&status);

        if (WIFEXITED(status))
        {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("Child process terminated abnormally\n");
        }
    }

    return (0);
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
        {NULL, NULL}
    };

    for (idx = 0; cbuiltins[idx].name; idx++)
    {
        if (strcmp(cbuiltins[idx].name, info->command) == 0)
        {
            // todo some counter
            result = cbuiltins[idx].handler(info);
            break;
        }

    }

    return (result);
}

void cmd_handler(g_data *info)
{
     int str_size, i = 0, ret;

    // while (ret != -1 ) {
        // printf("Enter a command to %s\n", info.av[0]);
        // printf("$ ");
        write(STDOUT_FILENO, "$ " , 2);

        fgets(info->command, sizeof(info->command), stdin);

      
        str_size = strlen(info->command);
        if ( str_size > 0 && info->command[str_size - 1] == '\n') {
            info->command[str_size - 1] = '\0';
        }

        parseCommand(info->command, info->arguments);
       
        // printPathDirectories(env);
        // puts("\n");
        // puts("\n");


        // implement builtins here
        ret = handle_builtins(info);
        if (ret == -1) 
        {
            char* commandPath =  findCommandPath(info->command);

            if (commandPath != NULL) {
                printf("Command path: %s\n", commandPath);
                exec_cmd(info, commandPath);
                
                free(commandPath);
            }
            else {
                if (info->arguments[0][0] == '/' && is_cmd(info->arguments[0]) == 1)
                {
                    exec_cmd(info, info->arguments[0]);
                    free(commandPath);
                }
                else
                {
                    // printf("Command not found in any path.\n");
                    // print_error(info, "Command not found in any path.");
                    p_error(info);
                }   
            }
        }
           atexit(report_mem_leak);

    // }
}

int exit_func(g_data *info)
{
    // char *leak_test;
    // leak_test = malloc(sizeof(char));

    printf("Hello world\n");
    return (0);
}