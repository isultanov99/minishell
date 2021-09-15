/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:50:39 by cpablo            #+#    #+#             */
/*   Updated: 2021/09/15 19:38:26 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t size)
{
	void	*buf;

	buf = malloc(size);
	if (buf == 0)
		return (NULL);
	ft_bzero(buf, size);
	return (buf);
}
