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