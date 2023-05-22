#include "main.h"

char *_strpbrk(const char *str, const char *set)
{
    const char *tr;
    while (*str != '\0')
    {
        tr = set;
        while (*tr != '\0')
        {
            if (*tr == *str)
            {
                return ((char*)str);
            }
            tr++;
        }
        str++;
    }
    return (NULL);
}

char *_sttrtok(char *p, const char *delim)
{
    static char *t = NULL;
    static char *nt = NULL;
    char *dp, *ct;

    if (p != NULL)
    {
        t = p;
        nt = p;
    }

    if (t == NULL)
    {
        return (NULL);
    }

    dp = _strpbrk(nt, delim);

    if (dp != NULL)
    {
        *dp = '\0';
        ct = t;
        t = dp + 1;
        nt = t;
        return (ct);
    }
    else if (*t != '\0')
    {
        ct = t;
        t = NULL;
        return (ct);
    }

    return (NULL);
}

int _getline(char **line, size_t len, int fd)
{
    int i = 0;
    size_t buffer_size = len;
    char *buff = *line;
    int bufffer_allocated = 0;

    if (line == NULL)
        return -1;

    if (buff == NULL)
    {
        bufffer_allocated = 1;
        buffer_size  = 128;
        buff = malloc(sizeof(char *) * buffer_size);
        if (buff == NULL)
            return -1;
    }
    while (((read(fd, &buff[i], 1)) > 0) && buff[i] != '\n')
    {
        i++;
        if (i > buffer_size -1)
        {
            char *nb = realloc(buff, sizeof(char *) * (buffer_size * 2));
            if (nb == NULL)
            {
                free(nb);
                return -1;
            }
            buff = nb;
        }
    }
    buff[i] = '\0';
    *line = buff;

    if (bufffer_allocated == 1)
        free(buff);

    return (i);
}


