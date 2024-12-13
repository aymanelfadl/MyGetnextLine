#include "get_next_line.h"

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