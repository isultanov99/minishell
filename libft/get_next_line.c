/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:14:59 by bmangree          #+#    #+#             */
/*   Updated: 2021/01/04 23:12:23 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strdup(const char *s)
{
	char		*copy;
	const int	s_len = gnl_strlen(s);

	copy = gnl_calloc(s_len + 1);
	if (!(copy))
		return (NULL);
	gnl_strlcpy(copy, s, s_len);
	return (copy);
}

int	readremainder(char **remainder, char **line)
{
	int		len;
	char	*tmp;
	int		i;

	len = gnl_strchr(*remainder, '\n') - *remainder + 1;
	*line = gnl_calloc(len);
	if (!(*line))
		return (ERROR);
	if (len != 1)
		gnl_strlcpy(*line, *remainder, len - 1);
	len = gnl_strlen(*remainder) - len;
	i = gnl_strlen(*remainder) - 1;
	tmp = gnl_calloc(len + 1);
	while (len-- > 0)
		tmp[len] = (*remainder)[i--];
	free(*remainder);
	*remainder = gnl_strdup(tmp);
	free(tmp);
	return (SUCCESS);
}

char	*join(char **remainder, char *buf, int rb)
{
	char	*tmp;

	if (*remainder != NULL)
	{
		tmp = gnl_strdup(*remainder);
		free(*remainder);
		*remainder = gnl_strjoin(tmp, buf, rb);
		free(tmp);
	}
	else
		*remainder = gnl_strjoin(*remainder, buf, rb);
	return (*remainder);
}

int	handle_last_line(char **remainder, char **line, char **buf)
{
	int	i;

	if (*remainder == NULL)
	{
		*line = gnl_calloc(1);
		if (!(*line))
			return (ERROR);
		free(*buf);
		return (EOFILE);
	}
	i = gnl_strlen(*remainder);
	*line = gnl_calloc(i + 1);
	if (!(*line))
		return (ERROR);
	gnl_strlcpy(*line, *remainder, i);
	free(*remainder);
	*remainder = NULL;
	free(*buf);
	return (EOFILE);
}

int	get_next_line(int fd, char **line)
{
	static char	*remainder;
	int			rb;
	int			res;
	char		*buf;

	buf = gnl_calloc(BUFFER_SIZE + 1);
	rb = read(fd, buf, BUFFER_SIZE);
	if (BUFFER_SIZE <= 0 || !(buf) || fd < 0
		|| rb < 0 || line == NULL)
		return (ERROR);
	while (rb || gnl_strchr(remainder, '\n'))
	{
		remainder = join(&remainder, buf, rb);
		if (!(remainder))
			return (ERROR);
		if (remainder && (gnl_strchr(remainder, '\n')))
		{
			res = readremainder(&remainder, line);
			if (res == SUCCESS)
				free(buf);
			return (res);
		}
		rb = read(fd, buf, BUFFER_SIZE);
	}
	return (handle_last_line(&remainder, line, &buf));
}
