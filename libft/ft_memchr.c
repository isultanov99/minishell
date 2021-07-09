/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 00:36:26 by bmangree          #+#    #+#             */
/*   Updated: 2020/11/16 17:03:12 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*soc;

	soc = s;
	while (n--)
	{
		if (*soc++ == (unsigned char)c)
			return ((void *)--soc);
	}
	return (NULL);
}
