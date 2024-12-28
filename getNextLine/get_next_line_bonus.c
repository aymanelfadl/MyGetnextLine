/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 23:30:31 by aelfadl           #+#    #+#             */
/*   Updated: 2024/12/27 23:35:04 by aelfadl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	if (!res)
		return (free(res), NULL);
	res[len] = '\0';
	return (res);
}

char	*ft_creatbuffer(int fd, char *buffer)
{
	ssize_t	bytes_read;
	char	*temp_buffer;
	char	*new_buffer;

	temp_buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(temp_buffer), NULL);
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

char	*ft_update_holder(char *buffer)
{
	if (ft_strchr(buffer, '\n'))
		return (ft_strdup(ft_strchr(buffer, '\n')));
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*holder[MAX_FD];
	char		*line;
	char		*buffer;

	line = NULL;
	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	buffer = ft_creatbuffer(fd, holder[fd]);
	if (!buffer || !*buffer)
		return (free(buffer), NULL);
	line = get_line(buffer);
	if (!line)
		return (free(buffer), NULL);
	holder[fd] = ft_update_holder(buffer);
	return (free(buffer), line);
}

// #include <unistd.h>
// #include <fcntl.h>

// int main()
// {
// 	int fd1 = open("isma.txt", O_RDONLY);
// 	int fd2 = open("test.txt", O_RDONLY);
// 	if (fd1 == -1 || fd2 == -1)
// 	{
// 		perror("err:");
// 		return 1;
// 	}
// 	char *d = get_next_line(fd1);
// 	printf("%s",d);
// 	free(d);
// 	d = get_next_line(fd2);
// 	printf("%s", d);
// 	free(d);
// 	close(fd1);
// 	close(fd2);
// 	return 0;
// }