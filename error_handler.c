#include "main.h"

int error_handler(g_data *info, int err_val)
{
    char *er_str;

    switch(err_val)
    {
        case -1:
            er_str = env_err(info);
            break;
        case 2:
            if (_strcmp("exit", info->arguments[0]) == 0)
            er_str = exit_shell_err(info);
            else
            er_str = get_cd_error(info)
;
        case 126:
            er_str = path_126_err(info);
            break;
        case 127:
            er_str = not_found_err(info);
    }

	if (er_str)
	{
		write(STDERR_FILENO, er_str, _strlen(er_str));
		free(er_str);
	}

    return (err_val);
}

char *env_err(g_data *info)
{
    int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = atoi_rev(info->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(info->file_name) + _strlen(ver_str);
	length += _strlen(info->arguments[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, info->file_name);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, info->arguments[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}

/**
 * atoi_rev - function converts int to string.
 * @n: type int number
 * Return: String.
 */
char *atoi_rev(int n)
{
    unsigned int num;
	int lenght = get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenght + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenght) = '\0';

	if (n < 0)
	{
		num = n * -1;
		buffer[0] = '-';
	}
	else
	{
		num = n;
	}

	lenght--;
	do {
		*(buffer + lenght) = (num % 10) + '0';
		num = num / 10;
		lenght--;
	}
	while (num > 0)
		;
	return (buffer);
}

/**
 * get_len - Get the lenght of a number.
 * @n: type int number.
 * Return: Lenght of a number.
 */
int get_len(int n)
{
	unsigned int n1;
	int lenght = 1;

	if (n < 0)
	{
		lenght++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		lenght++;
		n1 = n1 / 10;
	}

	return (lenght);
}

/**
 * path_126_err - error message for path and failure denied permission.
 * @info: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *path_126_err(g_data *info)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = atoi_rev(info->counter);
	length = _strlen(info->file_name) + _strlen(ver_str);
	length += _strlen(info->arguments[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, info->file_name);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, info->arguments[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * not_found_err - generic error message for command not found
 * @info: data relevant (counter, arguments)
 * Return: Error message
 */
char *not_found_err(g_data *info)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = atoi_rev(info->counter);
	length = _strlen(info->file_name) + _strlen(ver_str);
	length += _strlen(info->arguments[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, info->file_name);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, info->arguments[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * exit_shell_err - generic error message for exit in get_exit
 * @info: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *exit_shell_err(g_data *info)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = atoi_rev(info->counter);
	length = _strlen(info->file_name) + _strlen(ver_str);
	length += _strlen(info->arguments[0]) + _strlen(info->arguments[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, info->file_name);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, info->arguments[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, info->arguments[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}

/**
 * get_cd_error - error message for cd command in get_cd
 * @info: data relevant (directory)
 * Return: Error message
 */
char *get_cd_error(g_data *info)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = atoi_rev(info->counter);
	if (info->arguments[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(info->arguments[1]);
	}

	length = _strlen(info->file_name) + _strlen(info->arguments[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_cd(info, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * strcat_cd - function that concatenates the message for cd error
 *
 * @datash: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @ver_str: counter lines
 * Return: error message
 */
char *strcat_cd(g_data *info, char *msg, char *error, char *ver_str)
{
	char *flag;

	_strcpy(error, info->file_name);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, info->arguments[0]);
	_strcat(error, msg);
	if (info->arguments[1][0] == '-')
	{
		flag = malloc(3);
		flag[0] = '-';
		flag[1] = info->arguments[1][1];
		flag[2] = '\0';
		_strcat(error, flag);
		free(flag);
	}
	else
	{
		_strcat(error, info->arguments[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}
