
#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	lens1;
	size_t	lens2;

	lens1 = 0;
	lens2 = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		lens1 += strlen(s1);
	if (s2)
		lens2 += strlen(s2);
	res = (char *)calloc((lens1 + lens2 + 1), sizeof(char));
	if (!res)
		return (NULL);
	memcpy(res, s1, lens1);
	memcpy(res + lens1, s2, lens2);
	return (res);
}

char *get_line(char *buff)
{
    char *res;
    int len;

    len = 0;
    while (buff[len] && buff[len]!= '\n')
        len++;
    res = malloc(len++ + 1);
    if(!res)
    {
        free(buff);
        return NULL;
    }
    res[len + 1] = '\0';
    while(len >= 0)
    {
        len--;
        res[len] = buff[len];
    }
    return res;
}

char *get_next_line(int fd)
{
    char *buffer;
    char *tmpbuf;
    static char *holder;

    buffer = NULL;
    tmpbuf = malloc(BUFFER_SIZE);
    if (!tmpbuf)
        free(tmpbuf);
    if (read(fd, tmpbuf, BUFFER_SIZE) > -1)
    {
            buffer = ft_strjoin(buffer, holder);
            buffer = ft_strjoin(buffer, tmpbuf);
            while (!strchr(buffer,'\n'))
            {
                int i = read(fd, tmpbuf, BUFFER_SIZE);
                buffer = ft_strjoin(buffer, tmpbuf);
                if (i == 0)
                    return get_line(buffer); 
            }
            holder = strchr(buffer,'\n') + 1;
            return get_line(buffer);
    }
    return NULL;
    
}

int main()
{
    int fd = open("file.txt", O_RDONLY);
    if (fd < 0)
        return 0;
    printf("1:%s",get_next_line(fd));
    printf("2:%s",get_next_line(fd));
    printf("3:%s",get_next_line(fd));

}