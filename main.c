#include "main.h"

int main(int c, char **av, char **env)
{
    g_data info;

    init_g_data(&info, av, env, c);
    cmd_handler(&info, c);
}


char* sh_read_line(g_data *info) {
    char *line = NULL;
    static size_t buflen = 0;

    if (_getline(&line, buflen, info->readfd) == -1)
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

void process_interactive_commands(g_data *info)
{
    int ret = 1;

    while (ret == 1)
    {
        write(STDOUT_FILENO, "$ " , 2);
        fflush(stdout);

        strcpy(info->command, sh_read_line(info));
        fflush(stdin);

        _strcspn(info->command);
        if (strlen(info->command) == 0) 
        {
            ret = 1;
            continue;
        }
        ret = find_and_exec_cmd(info);

        info->counter += 1;
    }
}

int process_file_commands(g_data *info, int fd)
{
    char *line = NULL;
    static size_t len = 0;

    info->readfd = fd;

        if (fd == -1) {
           if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eprint_one_line(info->file_name);
				_eprint_one_line(": 0: Can't open ");
				_eprint_one_line(info->file);
				exit(127);
			}
			return (EXIT_FAILURE);
        }

        while (_getline(&line, len, fd)) {
            _strcpy(info->command, line);
            // Remove trailing newline character
            _strcspn(info->command);

            find_and_exec_cmd(info);
        }

    close(fd);
    return (1);
}

int process_non_interactive_commands(g_data *info)
{
    int ret = 0;

    info->readfd = 0;

    strcpy(info->command, sh_read_line(info));
    fflush(stdin);

    _strcspn(info->command);
    ret = find_and_exec_cmd(info);

    return (ret);
}
