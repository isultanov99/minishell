/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:50:39 by cpablo            #+#    #+#             */
/*   Updated: 2021/09/14 14:24:10 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t size)
{
	void	*buf;

	buf = malloc(size);
	if (buf == NULL)
		return (NULL);
	ft_bzero(buf, size);
	return (buf);
}
