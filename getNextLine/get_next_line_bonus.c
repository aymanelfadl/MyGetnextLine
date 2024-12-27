/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelfadl <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 20:30:02 by aelfadl           #+#    #+#             */
/*   Updated: 2024/12/14 20:30:04 by aelfadl          ###   ########.fr       */
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
	temp_buffer = malloc((size_t)BUFFER_SIZE  + 1);
	if (!temp_buffer)
		return (NULL);
	while (1)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(temp_buffer);
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

char *ft_update_holder(char *buffer)
{
	char *new_holder;
	
	if (ft_strchr(buffer, '\n'))
		new_holder = ft_strdup(ft_strchr(buffer, '\n'));
	else 
		new_holder = ft_strdup(ft_strchr(buffer, '\0')); 
	return new_holder;
}

char	*get_next_line(int fd)
{
	static char	*holder[MAX_FD];
	char 	*line;
	char 	*buffer;

	line = NULL;
	buffer = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	buffer = ft_creatbuffer(fd, holder[fd]);
	if (!buffer || !*buffer)
	{
		free(buffer);
		return (NULL);
	}
	line = get_line(buffer);
	if (!line)
		return (free(buffer), NULL);
	holder[fd] = ft_update_holder(buffer);
	free(buffer);
	return (line);
}

// #include <fcntl.h>
// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>

// int main() {
//     int fd = open("isma.txt", O_RDONLY);
//     if (fd == -1) {
//         perror("Failed to open file");
//         return 1; // Return error code if file open fails
//     }
	
//     int fd1 = open("test.txt", O_RDONLY);
//     if (fd == -1) {
//         perror("Failed to open file");
//         return 1; // Return error code if file open fails
//     }
	
//     char *d = NULL;  // Initialize the pointer
//     while ((d = get_next_line(fd)) != NULL) {
// 		printf("line :> %s", d);
// 		printf("%s",get_next_line(fd1));
//         free(d);  // Free the memory allocated by get_next_line
//     }
//     close(fd);  // Don't forget to close the file descriptor

//     return 0;
// }
