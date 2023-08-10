#ifndef GET_NEXT_LINE_H
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

char	*get_next_line(int fd);

#endif