/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 19:15:02 by bmangree          #+#    #+#             */
/*   Updated: 2021/01/04 20:23:15 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	gnl_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*gnl_calloc(int size)
{
	char	*p;
	int		i;

	i = 0;
	p = malloc(size);
	if ((p))
	{
		while (i < size)
		{
			p[i] = '\0';
			i += 1;
		}
	}
	else
		return (NULL);
	return (p);
}

int	gnl_strlcpy(char *dst, const char *src, int dstsize)
{
	int	retval;
	int	i;

	if (src == 0)
		return (0);
	retval = gnl_strlen(src);
	i = 0;
	if (dstsize != 0)
	{
		while (i < dstsize)
		{
			dst[i] = src[i];
			i += 1;
		}
	}
	return (retval);
}

char	*gnl_strjoin(char *s1, char *s2, int rb)
{
	int		len;
	int		i;
	char	*s;

	if (s1 != NULL)
		len = gnl_strlen(s1) + rb;
	else
		len = rb;
	i = 0;
	s = gnl_calloc(len + 1);
	if (!(s))
		return (NULL);
	while (s1 != NULL && *s1)
		s[i++] = *s1++;
	while (i != len)
		s[i++] = *s2++;
	return (s);
}

char	*gnl_strchr(const char *s, int c)
{
	char	chr;

	chr = c;
	if (s == NULL)
		return (NULL);
	while (*s != chr)
	{
		if (*s == '\0')
			return (NULL);
		s++;
	}
	return ((char *)s);
}
