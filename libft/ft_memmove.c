/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:01:36 by bmangree          #+#    #+#             */
/*   Updated: 2020/11/16 19:51:07 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*sorc;
	char		*dest;
	const char	*last_src;
	char		*last_dst;

	if (dst == NULL && src == NULL)
		return (NULL);
	sorc = (char *)src;
	dest = (char *)dst;
	if (dest < sorc)
		while (len--)
			*dest++ = *sorc++;
	else
	{
		last_src = sorc + len - 1;
		last_dst = dest + len - 1;
		while (len--)
			*last_dst-- = *last_src--;
	}
	return (dst);
}
