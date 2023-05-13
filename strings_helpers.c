#include "main.h"

/**
 * _strcmp - compares length of a string
 * @s: string to compare
 * @t: string to compare
 * Return: Always zero
 */

int _strcmp(const char *s, const char *t)
{
	while (*s && (*s == *t))
	{
		++s;
		++t;
	}
	return (*(const unsigned char *)s - *(const unsigned char *)t);
}

/**
 * _strcpy - copies a string into another variable
 * @dest: Variable to copy string into
 * @src: Variable to copy string from
 * Return: Always a char
 */

char *_strcpy(char *dest, char *src)
{
	int n = 0;

	while (src[n] != '\0')
	{
		dest[n] = src[n];
		n++;
	}
	dest[n] = '\0';
	return (dest);
}

/**
 * _strdup - duplicate a string
 * @s: string to duplicate
 * Return: Always a string
 */

char *_strdup(char *s)
{

	size_t e = _strlen(s) + 1;
	char *n = malloc(e);

	if (n == NULL)
	{
		return (NULL);
	}
	_memcpy(n, s, e);
	return (n);
}

/**
 * _strlen - Counts the number of char in a string
 * @s: the string
 * Return: Always a number
 */

int _strlen(char *s)
{
	int count = 0;

	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}

/**
 * _strncat - Concanate string
 * @t: A variable
 * @s: A variable
 * @n: Number of string to concanate
 * Return: Always a char
 */

char *_strncat(char *t, const char *s, int n)
{
	char *o = t;

	while (*t != '\0')
	{
		t++;
	}
	while (*s != '\0' && n > 0)
	{
		*t++ = *s++;
		n--;
	}
	*t = '\0';
	return (o);
}

