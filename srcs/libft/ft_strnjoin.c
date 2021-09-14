/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:54:07 by cpablo            #+#    #+#             */
/*   Updated: 2020/11/11 20:32:30 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	char	*new;
	int		i;

	i = 0;
	if (ft_strlen(s2) < n)
		new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	else
		new = malloc(ft_strlen(s1) + n + 1);
	if (!new)
		return (NULL);
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (*s2 && --n >= 0)
		new[i++] = *s2++;
	new[i] = '\0';
	free(s1);
	return (new);
}
