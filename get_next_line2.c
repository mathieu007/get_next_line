/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 08:05:20 by math              #+#    #+#             */
/*   Updated: 2023/03/10 07:20:39 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

bool	read_copy_buffer(int32_t fd, char *buffer, char *line, int32_t i)
{
	static int32_t	buf_i;
	int32_t			rd;

	if (!*buffer)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
			return (*buffer = 0, buf_i = 0, free_line(&line), false);
		if (rd < BUFFER_SIZE)
			buffer[rd] = '\0';
		if (rd == 0)
			return (*buffer = 0, buf_i = 0, true);
	}
	while (buffer[buf_i] && line[i])
	{
		line[i++] = buffer[buf_i];
		if (buffer[buf_i++] == '\n')
			return (line[i] = '\0', i = 0, true);
	}
	if (!buffer[buf_i] && buf_i < BUFFER_SIZE)
		return (line[i] = '\0', i = 0, true);
	return (false);
}

char	*resize_line(char *buffer, char *line, int32_t line_len)
{
	char	*temp;
	int32_t	i;

	i = 0;
	while (buffer[i])
		if (buffer[i++] == '\n')
			break ;
	temp = line;
	line_len += i;
	line = malloc(line_len + 1);
	if (!line)
		return (free_line(&temp), NULL);
	line[line_len] = '\0';
	if (temp)
		free(temp);
	return (line);
}

char	*get_next_line(int32_t fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int32_t		i;
	int32_t		line_len;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	line_len = 0;
	line = resize_line(buffer, line, &line_len);
	i = 0;
	while (true)
	{
		if (read_copy_buffer(fd, buffer, line, i))
			return (line);
		line = resize_line(buffer, line, line_len);
	}
}

// int	main(void)
// {
// 	int32_t	fd;
// 	char	*ret;

// 	fd = open("multiple_line_with_nl", O_RDWR);
// 	ret = get_next_line(fd);
// 	printf("line:%s", ret);
// 	free(ret);
// 	ret = get_next_line(fd);
// 	printf("line:%s", ret);
// 	free(ret);
// 	ret = get_next_line(fd);
// 	printf("line:%s", ret);
// 	free(ret);
// 	close(fd);
// }
