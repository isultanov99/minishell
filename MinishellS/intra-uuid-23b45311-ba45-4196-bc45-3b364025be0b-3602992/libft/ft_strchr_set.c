/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 15:32:33 by natali            #+#    #+#             */
/*   Updated: 2021/06/07 15:34:52 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_set(char *str, char *set)
{
	if (str && set)
	{
		while (*set)
		{
			if (ft_strchr(str, *set))
				return (ft_strchr(str, *set));
			set++;
		}
	}
	return (NULL);
}
