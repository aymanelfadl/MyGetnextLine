#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "get_next_line_bonus.h"

int main() {
     int fd = open("isma.txt", O_RDONLY);
     if (fd == -1) {
         perror("Failed to open file");
         return 1;
     }
 	char *d;
 	while(d= get_next_line(fd))
 	{
 		printf("%s",d);
		free(d);
 	}
 	close(fd);
     return 0;
}
