/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:19:35 by zait-bel          #+#    #+#             */
/*   Updated: 2023/12/19 15:46:42 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_buffer(char *buffer, char *res, int fd)
{
	ssize_t	i;

	while (!ft_strchr(buffer, '\n'))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == 0 || i == -1)
			break ;
		buffer[i] = '\0';
		res = ft_strjoin(res, buffer);
	}
	free(buffer);
	return (res);
}

static char	*get_line(char *line)
{
	char	*res;
	char	*result;
	size_t	i;

	i = 0;
	res = NULL;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	result = ft_strdup(&line[i]);
	if (!result)
		return (free(line), NULL);
	line[i] = '\0';
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*res;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX || BUFFER_SIZE > INT_MAX)
		return (free(res), res = NULL, NULL);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (free(res), res = NULL, NULL);
	buffer[0] = 0;
	line = get_buffer(buffer, res, fd);
	if (!line)
		return (res = NULL, NULL);
	if (!*line)
		return (free (res), res = NULL, NULL);
	res = get_line(line);
	if (!res)
		return (NULL);
	buffer = ft_strdup(line);
	free (line);
	if (!buffer)
		return (free(res), res = NULL, NULL);
	return (buffer);
}
