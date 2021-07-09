/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 03:56:44 by bmangree          #+#    #+#             */
/*   Updated: 2020/11/17 00:17:47 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*sorc;
	char		*dest;

	if (dst == NULL && src == NULL)
		return (NULL);
	sorc = (char *)src;
	dest = (char *)dst;
	while (n--)
		*dest++ = *sorc++;
	return (dst);
}
