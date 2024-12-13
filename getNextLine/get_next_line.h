# ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H


#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 5

char *get_next_line(int fd);
char *ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);

#endif