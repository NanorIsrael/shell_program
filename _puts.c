#include "main.h"

/** _puts - print strings with new line
 * @s: the string to print
 */

void _puts(const char *s)
{
        while (*s != '\0')
        {
                _putchar(*s);
                s++;
        }
        _putchar('\n');
}


/**
 * _prerror - Prints an error message indicating that a command is not found
 * @e: The name of the command that was not found
 *
 * Return: void
 */

void _prerror(char *e)
{
        char *y;

        y = malloc(sizeof(char *) * _strlen(e) + _strlen(" :not found"));
        y = _strcat(e, ":not found");
        write(STDOUT_FILENO, y, _strlen(y));
        write(STDOUT_FILENO, "\n", 1);
}