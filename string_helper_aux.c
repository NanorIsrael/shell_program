#include "main.h"

char *_strcspn(char *str)
{
    int str_size;

    str_size = _strlen(str);
    if ( str_size > 0 && str[str_size - 1] == '\n')
    {
        str[str_size - 1] = '\0';
    }
    return (str);
}

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
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
