/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zait-bel <zait-bel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:34:23 by zait-bel          #+#    #+#             */
/*   Updated: 2023/12/19 15:53:14 by zait-bel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*res[OPEN_MAX];
	char		*buffer;
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX)
		return (NULL);
	if (BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (free(res[fd]), res[fd] = NULL, NULL);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (free(res[fd]), res[fd] = NULL, NULL);
	buffer[0] = 0;
	line = get_buffer(buffer, res[fd], fd);
	if (!line)
		return (res[fd] = NULL, NULL);
	if (!*line)
		return (free (res[fd]), res[fd] = NULL, NULL);
	res[fd] = get_line(line);
	if (!res[fd])
		return (NULL);
	buffer = ft_strdup(line);
	free(line);
	if (!buffer)
		return (free(res[fd]), res[fd] = NULL, NULL);
	return (buffer);
}
