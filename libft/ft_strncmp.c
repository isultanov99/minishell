/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 21:49:20 by bmangree          #+#    #+#             */
/*   Updated: 2021/05/18 18:20:58 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n)
	{
		if ((unsigned char)*s1++ == (unsigned char)*s2++
			&& ((unsigned char)*s1 != '\0' || (unsigned char)*s2 != '\0'))
			n--;
		else
			return ((unsigned char)*--s1 - (unsigned char)*--s2);
	}
	return (0);
}
