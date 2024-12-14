#include "get_next_line.h"

char	*get_line(char *buff)
{
	int		len;
	char	*res;

	len = 0;
	while (buff[len] && buff[len] != '\n')
		len++;
	if (buff[len] == '\n')
		len++;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, buff, len);
	res[len] = '\0';
	return (res);
}
char	*ft_update_holder(char **holder)
{
	char	*temp;

	if (*holder)
	{
		temp = ft_strdup(*holder);
		free(*holder);
		*holder = NULL;
	}
	else
		temp = ft_strdup("");
	return (temp);
}

char	*ft_creatbuffer(int fd, char *buffer)
{
	size_t	bytes_read;
	char	*temp_buffer;
	char	*new_buffer;

	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		temp_buffer[bytes_read] = '\0';
		new_buffer = ft_strjoin(buffer, temp_buffer);
		free(buffer);
		buffer = new_buffer;
		if (ft_strchr(buffer, '\n') || bytes_read == 0)
			break ;
	}
	free(temp_buffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*holder = NULL;

	char *line, *buffer, *temp;
	line = NULL;
	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = ft_update_holder(&holder);
	buffer = ft_creatbuffer(fd, temp);
	if (!buffer || !*buffer)
	{
		free(buffer);
		return (NULL);
	}
	line = get_line(buffer);
	if (ft_strchr(buffer, '\n'))
		holder = ft_strdup(ft_strchr(buffer, '\n') + 1);
	free(buffer);
	return (line);
}
