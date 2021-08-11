/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 17:49:00 by natali            #+#    #+#             */
/*   Updated: 2021/07/28 17:49:11 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**arr_cpy(char **array)
{
	int		i;
	int		len;
	char	**copy;

	len = arr_len((void **)array);
	copy = (char **)malloc(sizeof(char *) * (len + 1));
	i = -1;
	while (++i < len)
		copy[i] = ft_strdup(array[i]);
	copy[i] = NULL;
	return (copy);
}
