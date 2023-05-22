#include "main.h"

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
        // wait(&status);
        // check waitpid

        if (waitpid(pid, &status, WUNTRACED)  == -1)
        {
            // printf("Child process exited with status: %d\n", WEXITSTATUS(status));
            perror("wait");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            // printf("Child process terminated abnormally\n");
            // _puts("Error: Command execution failed");
            exit(EXIT_FAILURE);
        }
    }

    return (1);
}

void cmd_handler(g_data *info, int c)
{
    int fd = -1;

    if (c == 1 && is_shell_interactive())
    {
        process_interactive_commands(info);
    }
    else if (c == 2)
    {
        fd = open(info->file, O_RDONLY);
        process_file_commands(info, fd);
    }
    else
    {
        if (process_non_interactive_commands(info) == 0)
        {
            file_error(info);
            exit(EXIT_FAILURE);
        }
    }
    
    free_all(info);
    atexit(report_mem_leak);
}

int find_and_exec_cmd(g_data *info)
{
    int ret = 0;

    parseCommand(info);
    ret = handle_builtins(info);
     if (ret == -1) 
    {     
        ret = path_finder(info);
    }
    return (ret);
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

int path_finder(g_data *info)
{
    int ret = 0;
    char *commandPath = find_command_path(info->command);

            if (commandPath != NULL) {
                // printf("Command path: %s\n", commandPath);
                ret = exec_cmd(info, commandPath);
                
                free(commandPath);
            }
            else {
                    if (info->arguments[0])
                    {
                        if (info->arguments[0][0] == '/' && is_cmd(info->arguments[0]) == 1)
                        {
                            ret = exec_cmd(info, info->arguments[0]);
                            free(commandPath);
                        }
                        else
                        {
                            // check if is an alias and execute here
                            error_handler(info, 127);
                            ret = 1;
                        }   
                    }
            }
    return (ret);
}
