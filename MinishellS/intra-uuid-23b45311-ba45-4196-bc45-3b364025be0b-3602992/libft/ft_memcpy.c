/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 22:07:11 by lkarliah          #+#    #+#             */
/*   Updated: 2021/07/26 17:07:58 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*s1;
	unsigned const char	*s2;

	s1 = (unsigned char *)dst;
	s2 = (unsigned const char *)src;
	if (dst == NULL || src == NULL)
		return (NULL);
	while (n-- > 0)
		*s1++ = *s2++;
	return (dst);
}
