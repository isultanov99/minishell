/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 22:32:55 by lkarliah          #+#    #+#             */
/*   Updated: 2021/07/26 16:57:09 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*s1;
	const unsigned char	*s2;

	if (!dst || !src)
		return (NULL);
	s1 = (unsigned char *)dst;
	s2 = (const unsigned char *)src;
	while (n-- > 0)
	{
		if (*s2 == (unsigned char)c)
		{
			*s1++ = *s2++;
			dst = s1;
			return (dst);
		}
		*s1++ = *s2++;
	}
	return (NULL);
}
