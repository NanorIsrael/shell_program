#include "main.h"

/**
 * _atoi - converts a string to an interger
 * @src: pointer to the string to convert
 *
 * Return: the converted integer value
 */
int _atoi(const char *src)
{
	int n = 0;
	int s = 1;
	const char *p = src;

	while (*p == ' ' || *p == '\n' || *p == '\f')
	{
		p++;
	}
	if (*p == '-')
	{
		s = -1;
		p++;
	}
	else if (*p >= '0' && *p <= '9')
	{
		n = n * 10 + (*p - '0');
		p++;
	}

	return (n * s);
}

/**
 * _isalpha - entry point
 * @q: the chr
 * Return: always int
 */

int _isalpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * _memcpy - copies memory
 * @dest: a void pointer
 * @src: void pointer
 * @n: a variable
 */

void _memcpy(void *dest, const void *src, unsigned int n)
{
	char *srcptr = (char *)src;
	char *destptr = (char *)dest;

	while (n > 0)
	{
		destptr[n - 1] = srcptr[n - 1];
		n--;
	}
	destptr[n] = '\0';
}

/**
 * _strchr - it search for the occurance of a specified char
 * @r: The char to search from
 * @c: the char to search for
 * Return: always char
 */

char *_strchr(const char *r, char c)
{
	while (*r != '\0')
	{
		if (*r == c)
		{
			return ((char *) r);
		}
		r++;
	}
	return (NULL);
}

/**
 * _strcat - concatenate two strings
 * @dest: char pointer the dest of the copied str
 * @src: const char pointer the source of str
 * Return: the dest
 */
char *_strcat(char *dest, const char *src)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}