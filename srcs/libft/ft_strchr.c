/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:54:36 by cpablo            #+#    #+#             */
/*   Updated: 2020/11/11 19:54:37 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	while (*str != '\0' && *str != (char)ch)
		str++;
	if (*str == (char)ch)
		return ((char *)str);
	return (NULL);
}
