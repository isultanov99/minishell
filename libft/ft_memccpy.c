/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 08:05:33 by bmangree          #+#    #+#             */
/*   Updated: 2020/11/17 00:17:38 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src,
		int c, size_t n)
{
	const unsigned char	*sorc;
	unsigned char		*dest;

	sorc = src;
	dest = dst;
	while (n--)
	{
		*dest = *sorc;
		if (((*sorc) == (unsigned char)c))
			return (dest += 1);
		dest += 1;
		sorc += 1;
	}
	return (NULL);
}
