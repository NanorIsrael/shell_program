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

void _putchar(char c)
{
        if (!c)
                return;

        write(STDOUT_FILENO, &c, 1);
}

void _eputchar(char c)
{
        if (!c)
                return;

        write(STDERR_FILENO, &c, 1);
}

void _eputs(const char *s)
{
        while (*s != '\0')
        {
                _putchar(*s);
                s++;
        }
        _putchar('\n');
}

void _print_one_line(const char *s)
{
        while (*s != '\0')
        {
                _putchar(*s);
                s++;
        }
}