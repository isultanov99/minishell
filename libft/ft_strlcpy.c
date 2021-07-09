/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:40:52 by bmangree          #+#    #+#             */
/*   Updated: 2020/11/17 00:52:50 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	retval;

	if (src == 0)
		return (0);
	retval = ft_strlen(src);
	if (dstsize != 0)
	{
		while (*src && --dstsize)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (retval);
}
