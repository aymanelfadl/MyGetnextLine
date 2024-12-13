#include "get_next_line.h"


char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*ptr;
	size_t	i;

	len = strlen(s1);
	i = 0;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char *ft_strjoin(char const *s1, char const *s2)
{
    char *res;
    size_t lens1;
    size_t lens2;

    lens1 = 0;
    lens2 = 0;
    if (!s1 && !s2)
        return NULL;
    if (s1)
        lens1 = strlen(s1);
    if (s2)
        lens2 = strlen(s2);
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
    int len;
    char *res;

    len = 0;
    while (buff[len] && buff[len] != '\n')
        len++;
    if (buff[len] == '\n')
        len++;
    res = malloc(len + 1);
    if (!res)
        return NULL;
    memcpy(res, buff, len);
    res[len] = '\0';
    return res;
}

char *ft_creatbuffer(int fd,char *holder)
{
    char *tmpbuff;
    size_t bytes_read;
    char *newbuff;
    char *buffer;

    buffer = NULL;
    tmpbuff = malloc(BUFFER_SIZE);
    if (!tmpbuff)
        return NULL;
    if (holder)
    {
        newbuff = ft_strdup(holder);
        free(holder);
    }
    else
        newbuff = ft_strdup("");
    while (1)
    {
        bytes_read = read(fd, tmpbuff, BUFFER_SIZE);
        
        if (bytes_read < 0)
        {
            free(tmpbuff);
            free(newbuff);
            return NULL;
        }

        buffer = ft_strjoin(newbuff, tmpbuff);
        free(newbuff);
        newbuff = buffer;
        
        if (strchr(tmpbuff, '\n') || bytes_read == 0)
        {
            holder = strchr(tmpbuff, '\n') + 1;
            break ;
        }
    }
    free(tmpbuff);
    return buffer;
}

char *get_next_line(int fd)
{
    static char *holder = NULL;
    char *buffer = NULL;

    if (fd < 0 || BUFFER_SIZE < 0)
        return NULL;
    buffer = ft_creatbuffer(fd, holder);
    if (!buffer)
        return NULL;
    char *l = get_line(buffer);
    free(buffer);
    return l;
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