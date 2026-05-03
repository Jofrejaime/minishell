/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutumbu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:30:03 by jmutumbu          #+#    #+#             */
/*   Updated: 2025/06/15 15:44:28 by jmutumbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t count)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	if (count == 0)
		return (0);
	while ((i < count - 1) && *s1 && *s2 && (*s1 == *s2))
	{
		s1 ++;
		s2 ++;
		i ++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
