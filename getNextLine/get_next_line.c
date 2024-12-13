#include "get_next_line.h"

char *ft_strjoin(char const *s1, char const *s2)
{
    char *res;
    size_t lens1;
    size_t lens2;

    if (s1 == NULL)
        lens1 = 0;
    else
        lens1 = strlen(s1);

    if (s2 == NULL)
        lens2 = 0;
    else
        lens2 = strlen(s2);

    if (!s1 && !s2)
        return NULL;

    res = malloc(lens1 + lens2 + 1);
    if (!res)
        return NULL;

    if (s1)
        memcpy(res, s1, lens1);
    if (s2)
        memcpy(res + lens1, s2, lens2);
    res[lens1 + lens2] = '\0';

    return res;
}

char *get_line(char *buff)
{
    int len = 0;
    while (buff[len] && buff[len] != '\n')
        len++;
    if (buff[len] == '\n')
        len++;
    char *res = malloc(len + 1);
    if (!res)
        return NULL;
    memcpy(res, buff, len);
    res[len] = '\0';
    return res;
}

char *get_next_line(int fd)
{
    static char *remainder = NULL;
    char *buffer = NULL;
    char *line = NULL;
    char *temp_buffer = NULL;
    ssize_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;

    temp_buffer = malloc(BUFFER_SIZE + 1);
    if (!temp_buffer)
        return NULL;
    if (remainder)
        buffer = strdup(remainder);
    else
        buffer = strdup("");
    free(remainder);
    remainder = NULL;
    while (1)
    {
        bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(temp_buffer);
            free(buffer);
            return NULL;
        }
        temp_buffer[bytes_read] = '\0';

        char *new_buffer = ft_strjoin(buffer, temp_buffer);
        free(buffer);
        buffer = new_buffer;

        if (strchr(buffer, '\n') || bytes_read == 0)
            break;
    }
    free(temp_buffer);
    if (!*buffer)
    {
        free(buffer);
        return NULL;
    }
    line = get_line(buffer);
    char *newline = strchr(buffer, '\n');
    if (newline)
        remainder = strdup(newline + 1);
    free(buffer);
    return line;
}

int main()
{
    int fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return 0;

    char *s;
    while ((s = get_next_line(fd)) != NULL)
    {
        printf("%s", s);
        free(s);
    }

    close(fd);
    return 0;
}