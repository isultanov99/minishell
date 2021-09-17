/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:33:41 by cpablo            #+#    #+#             */
/*   Updated: 2021/09/14 14:33:41 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc_arr(char **arr, size_t old_len, char *new_str)
{
	char	**new;
	size_t	i;

	if (!new_str)
		return (arr);
	new = (char **)malloc(sizeof(char *) * (old_len + 2));
	i = -1;
	while (++i < old_len)
		new[i] = ft_strdup(arr[i]);
	new[i] = ft_strdup(new_str);
	new[++i] = NULL;
	if (arr)
		array_free((void **)arr);
	return (new);
}
