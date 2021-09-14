/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:54:32 by cpablo            #+#    #+#             */
/*   Updated: 2020/11/11 19:54:33 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*result;
	size_t	len;
	int		i;

	len = ft_strlen(str) + 1;
	result = malloc(len);
	i = 0;
	if (!result)
		return (NULL);
	while (str[i] != '\0')
	{
		result[i] = str[i];
		++i;
	}
	result[i] = '\0';
	return (result);
}
