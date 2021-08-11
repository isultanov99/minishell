/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:22:22 by lkarliah          #+#    #+#             */
/*   Updated: 2021/07/26 16:59:47 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;

	if (!b)
		return (NULL);
	str = (unsigned char *)b;
	while (len-- > 0)
		*str++ = (unsigned char)c;
	return (b);
}
