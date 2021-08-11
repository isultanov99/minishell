/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 19:36:54 by natali            #+#    #+#             */
/*   Updated: 2021/08/04 16:39:11 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	char	*str1;
	char	*str2;
	int		i;

	i = 0;
	str1 = s1;
	str2 = s2;
	if (str1 && str2)
	{
		while (str1[i] == str2[i] && str1[i] && str2[i])
			i++;
		return (str1[i] - str2[i]);
	}
	return (-1);
}
