/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 22:18:56 by cpablo            #+#    #+#             */
/*   Updated: 2021/04/29 22:28:54 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *str)
{
	char	*result;
	size_t	len;
	int		i;

	len = ft_strlen(str) + 1;
	result = (char *)malloc(sizeof(char) * len);
	if (!result)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*check_remainder(char **remainder, char **line)
{
	char	*ptr_n;

	ptr_n = NULL;
	if (*remainder)
	{
		ptr_n = ft_strchr(*remainder, '\n');
		if (ptr_n)
		{
			*ptr_n = '\0';
			*line = ft_strdup(*remainder);
			ft_strcpy(*remainder, ++ptr_n);
		}
		else
		{
			*line = *remainder;
			*remainder = NULL;
		}
	}
	else
		*line = ft_strnew(1);
	return (ptr_n);
}

void	find_new_line(char **ptr_n, char **remainder, char *buf)
{
	char	*tmp;

	*ptr_n = ft_strchr(buf, '\n');
	if (*ptr_n)
	{
		*(*ptr_n) = '\0';
		(*ptr_n)++;
		tmp = *remainder;
		*remainder = ft_strdup(*ptr_n);
		free(tmp);
	}
}

int	get_next_line(int fd, char **line)
{
	static char		*remainder;
	t_gnl			gnl;

	gnl.bytes_read = 1;
	if (fd < 0 || BUFFER_SIZE < 1 || !line)
		return (-1);
	gnl.ptr_n = check_remainder(&remainder, line);
	while (!gnl.ptr_n && gnl.bytes_read != 0)
	{
		gnl.bytes_read = read(fd, gnl.buf, BUFFER_SIZE);
		if (gnl.bytes_read == -1)
		{
			gnl_free(line);
			return (-1);
		}
		gnl.buf[gnl.bytes_read] = '\0';
		find_new_line(&gnl.ptr_n, &remainder, gnl.buf);
		gnl_tmp(&gnl, line);
		if (!*line)
			return (-1);
	}
	if (!gnl.ptr_n)
		return (0);
	else
		return (1);
}
