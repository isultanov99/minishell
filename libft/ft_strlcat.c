/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 21:18:13 by bmangree          #+#    #+#             */
/*   Updated: 2020/11/17 00:52:50 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	retval;
	int		n;

	if (ft_strlen(dst) >= dstsize)
		return (dstsize + ft_strlen(src));
	retval = ft_strlen(dst) + ft_strlen(src);
	n = dstsize - ft_strlen(dst);
	if (dstsize != 0)
	{
		dst = dst + ft_strlen(dst);
		while (*src && n)
		{
			if (--n != 0)
			{
				*dst++ = *src;
			}
			src++;
		}
		*dst = '\0';
	}
	return (retval);
}
