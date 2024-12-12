# ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H


#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1

char *get_next_line(int fd);

#endif