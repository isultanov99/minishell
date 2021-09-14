/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:11:36 by cpablo            #+#    #+#             */
/*   Updated: 2020/11/11 19:55:08 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	unsigned char sym;
	unsigned char *arr;

	sym = (unsigned char)c;
	arr = (unsigned char *)destination;
	while (n-- > 0)
	{
		*arr++ = sym;
	}
	return (destination);
}
