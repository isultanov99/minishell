/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:34:47 by lkarliah          #+#    #+#             */
/*   Updated: 2021/07/26 17:02:03 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	const char	*src1;

	if (!dst || !src)
		return (0);
	src1 = src;
	if (!src1)
	{
		dst = NULL;
		return (0);
	}
	if (dstsize == 0)
		return (ft_strlen(src));
	i = dstsize - 1;
	while (i-- > 0 && *src1)
		*dst++ = *src1++;
	*dst = '\0';
	return (ft_strlen(src));
}
