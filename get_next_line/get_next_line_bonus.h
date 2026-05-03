/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutumbu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:25:36 by jmutumbu          #+#    #+#             */
/*   Updated: 2025/08/12 16:25:37 by jmutumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include "libft.h"

char	*get_next_line(int fd);
char	*extract_line(char **buffer);

int		create_buffer(char **buffer, char **temp_buffer, ssize_t bytes_read);
int		read_archive(int fd, char **buffer, char **temp_buffer);

#endif
