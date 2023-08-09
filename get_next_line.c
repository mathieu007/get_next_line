
#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

int	get_cpy_len(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (*str && *str != '\n')
	{
		len++;
		str++;
	}
	if (*str == '\n')
		return (len + 1);
	return (len);
}

char	*cpy_buff_to_line(char *buff, char *line, int buff_len)
{
	char	*old_line;
	int		i;
	char	*new;
	int		len;

	old_line = line;
	i = 0;
	len = ft_strlen(old_line) + buff_len;
	new = malloc(len + 1);
	new[len] = '\0';
	while (line && *line)
		new[i++] = *line++;
	while (i < len)
		new[i++] = *buff++;
	if (old_line)
		free(old_line);
	return (new);
}

static char	*get_line(char *buff, int fd, int buff_len)
{
	static char	*line;
	char		*cpy;

	cpy = line;
	if (buff_len == 0)
		return (line = NULL, cpy);
	line = cpy_buff_to_line(buff, line, buff_len);
	cpy = line;
	if (buff[buff_len - 1] == '\n')
		return (line = NULL, cpy);
	return (get_next_line(fd));
}

void	*free_line(char *buff, int fd)
{
	char	*line;

	*buff = '\0';
	line = get_line(buff, fd, 0);
	if (line)
		free(line);
	return (NULL);
}

int			fail_read = 0;

int	test_read(int fd, char *buff, int read_len)
{
	if (fail_read == 1)
		return (close(fd), -1);
	return (read(fd, buff, read_len));
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	static char	*curr;
	int			rd_len;
	int			cpy_len;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!curr || !*curr)
	{
		curr = buff;
		rd_len = test_read(fd, curr, BUFFER_SIZE);
		if (rd_len < 0)
			return (free_line(curr, fd));
		curr[rd_len] = '\0';
		if (rd_len == 0)
			return (get_line(curr, fd, 0));
	}
	cpy_len = get_cpy_len(curr);
	curr = &curr[cpy_len];
	return (get_line(&curr[-cpy_len], fd, cpy_len));
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s", line);
	if (line)
		free(line);
	line = get_next_line(fd);
	printf("%s", line);
	if (line)
		free(line);
	fail_read = 1;
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		fd = open("file.txt", O_RDONLY);
	}
	fail_read = 0;
	line = get_next_line(fd);
	printf("%s", line);
	if (line)
		free(line);
	line = get_next_line(fd);
	printf("%s", line);
	if (line)
		free(line);
	line = get_next_line(fd);
	printf("%s", line);
	if (line)
		free(line);
	line = get_next_line(fd);
	printf("%s", line);
	if (line)
		free(line);
	line = get_next_line(fd);
	printf("%s", line);
	if (line)
		free(line);
	close(fd);
	return (1);
}
