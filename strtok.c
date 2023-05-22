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

char *_getline(void)
{
    static char w[MAX_COMMAND_LENGTH];
    static int iy = 0;
    static int ne = 0;

    char c, *l = NULL;
    int ll = 0;
    l = (char *)malloc((MAX_COMMAND_LENGTH + 1) * sizeof(char));

    while (1)
    {
        if (iy >= ne)
        {
            iy = 0;
            ne = read(STDIN_FILENO, w, MAX_COMMAND_LENGTH);
            if (ne <= 0)
            {
                if (ll > 0)
                {
                    break;
                }
                else
                {
                    free(l);
                    return (NULL);
                }
            }
        }

        c = w[iy++];
        if (l == NULL)
        {
            return (NULL);
        }
        l[ll++] = c;
        if (c == '\n' || c == EOF)
        {
            break;
        }
    }
    l[ll] = '\0';
    return (l);
}