/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 23:10:33 by natali            #+#    #+#             */
/*   Updated: 2021/07/22 11:46:24 by natali           ###   ########.fr       */
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
