/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 15:30:14 by natali            #+#    #+#             */
/*   Updated: 2021/08/03 13:41:28 by natali           ###   ########.fr       */
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
		ft_free_array((void **)arr);
	return (new);
}
