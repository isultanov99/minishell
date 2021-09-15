/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:11:36 by cpablo            #+#    #+#             */
/*   Updated: 2021/09/15 19:46:25 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char	sym;
	unsigned char	*arr;

	sym = (unsigned char)c;
	arr = (unsigned char *)destination;
	while (n-- > 0)
	{
		*arr++ = sym;
	}
	return (destination);
}
