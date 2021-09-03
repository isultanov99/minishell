/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:44:02 by lkarliah          #+#    #+#             */
/*   Updated: 2021/04/25 02:39:21 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_joinchr(char *s1, char c)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(ft_strlen(s1) + 2);
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = c;
	new[++i] = '\0';
	return (new);
}

int	get_next_line(int fd, char **line)
{
	char	buf;
	char	*for_free;
	int		ret;

	if (fd < 0 || !line)
		return (-1);
	*line = ft_calloc(1);
	while (1)
	{
		ret = read(fd, &buf, 1);
		if (ret < 0)
			return (-1);
		if (ret == 0)
			return (0);
		if (buf && buf != '\n')
		{
			for_free = *line;
			*line = ft_joinchr(*line, buf);
			free(for_free);
		}
		if (buf == '\n')
			return (1);
	}
	return (1);
}
