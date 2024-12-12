
#include "get_next_line.h"


char	*ft_findnewline(char *s)
{
	char			*res;
    int i = 0;
    int len = 0;
	if (!s || !strchr(s,'\n'))
		return (NULL);
    while (s[len]!= '\n')
        len++;
    res = malloc(len + 1);
    if (!res)
        return NULL;
    res[len] = '\0'; 
    while(len >= 0)
    {
        len--;
        res[len] = s[len];
    }
    return res;
}

char *get_next_line(int fd)
{
    char *res;
    char *buffer;
    int len = 0;
    buffer = malloc(BUFFER_SIZE);
    if (!buffer)
        return NULL;
    if (read(fd, buffer, BUFFER_SIZE) < -1)
    {
        free(buffer);
        return NULL;
    }
    res = ft_findnewline(buffer);
    if (!res)
    {
        free(buffer);
        return NULL;
    }
    return res;
}

int main()
{
    int fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return 0;
    printf("%s",get_next_line(fd));
}