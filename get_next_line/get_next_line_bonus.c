/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutumbu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:25:19 by jmutumbu          #+#    #+#             */
/*   Updated: 2025/08/12 16:25:20 by jmutumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*temp_buffer;

	temp_buffer = NULL;
	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (!read_archive(fd, &buffer[fd], &temp_buffer))
	{
		buffer[fd] = NULL;
		temp_buffer = NULL;
		return (NULL);
	}
	if (!buffer[fd] || !buffer[fd][0])
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	return (extract_line(&buffer[fd]));
}

int	read_archive(int fd, char **buffer, char **temp_buffer)
{
	ssize_t	bytes_read;

	(*temp_buffer) = malloc(BUFFER_SIZE + 1);
	if (!(*temp_buffer))
		return (0);
	bytes_read = 1;
	while (!*buffer || (!ft_strchr(*buffer, '\n') && bytes_read > 0))
	{
		bytes_read = read(fd, *temp_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(*temp_buffer), free(*buffer), 0);
		if (bytes_read == 0)
			break ;
		(*temp_buffer)[bytes_read] = '\0';
		if (!create_buffer(buffer, temp_buffer, bytes_read))
		{
			if (*buffer)
				free(*buffer);
			free(temp_buffer);
			return (0);
		}
	}
	free(*temp_buffer);
	return (1);
}

int	create_buffer(char **buffer, char **temp_buffer, ssize_t bytes_read)
{
	char	*temp;

	temp = NULL;
	if (!(*buffer))
		(*buffer) = ft_substr(*temp_buffer, 0, bytes_read);
	else
	{
		temp = ft_strjoin(*buffer, *temp_buffer);
		free(*buffer);
		(*buffer) = temp;
	}
	if (!(*buffer))
		return (0);
	return (1);
}

char	*extract_line(char **buffer)
{
	char	*newline_pos;
	char	*temp;
	char	*line;

	temp = NULL;
	line = NULL;
	newline_pos = ft_strchr(*buffer, '\n');
	if (newline_pos)
	{
		line = ft_substr(*buffer, 0, newline_pos - *buffer + 1);
		temp = ft_substr(*buffer, newline_pos - *buffer + 1,
				ft_strlen(*buffer));
		free(*buffer);
		(*buffer) = temp;
	}
	else
	{
		line = ft_substr(*buffer, 0, ft_strlen(*buffer));
		if (line)
		{
			free(*buffer);
			(*buffer) = NULL;
		}
	}
	return (line);
}
