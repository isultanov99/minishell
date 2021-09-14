/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:54:07 by cpablo            #+#    #+#             */
/*   Updated: 2020/11/11 20:32:30 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	if (n == 0)
		return (0);
	i = 0;
	while ((str1[i] == str2[i]) && str1[i] && str2[i] && --n)
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
