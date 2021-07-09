/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 00:13:06 by bmangree          #+#    #+#             */
/*   Updated: 2021/05/18 18:21:54 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*copy;

	copy = malloc(ft_strlen(s) + 1);
	if (!(copy))
		return (NULL);
	ft_memcpy(copy, s, ft_strlen(s) + 1);
	return (copy);
}
