#include "main.h"

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
