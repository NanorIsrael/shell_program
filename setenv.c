#include "main.h"

int _existadd(char **env, char *buffer)
{
    size_t elen = 0;
    char **n;
    if (*env == NULL)
    {
        while (environ[elen] != NULL)
        {
                elen++;
        }
        n = (char **) malloc((elen + 2) * sizeof(char *));
        if (n == NULL) {
            free(buffer);
            return (-1);
        }
        environ = n;
        environ[elen] = buffer;
        environ[elen + 1] = NULL;
        free(n);
        }

       return (0);
}

int _setenv(const char *n, const char *val, int w)
    {
         char *buffer, **env = environ;
        size_t nlen = strlen(n),  vallen = strlen(val), bufferLen;
    if (n == NULL || n[0] == '\0' || strchr(n, '=') != NULL || val == NULL)
    {
        return (-1);
    }

    if (!w && getenv(n) != NULL)
     {
         return (0);
     }

     bufferLen= nlen + vallen + 2;
    buffer = (char *) malloc(bufferLen);

    if (buffer == NULL)
    {
        return (-1);
    }

    strcpy(buffer, n);
    strcat(buffer, "=");
    strcat(buffer, val);
    while (*env != NULL)
     {
        if (strncmp(*env, n, nlen) == 0 && (*env)[nlen] == '=')
        {
            if (w)
             {
              *env = buffer;
                //free(*env);
            }
            else
             {
              free(buffer);
              return (0);
            }
            break;
        }
        env++;
    }
     free(buffer);
    return (0);
}