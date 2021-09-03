/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natali <natali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 09:31:27 by natali            #+#    #+#             */
/*   Updated: 2021/08/04 14:32:04 by natali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	arr_len(void **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

void	*ft_free_array(void **array)
{
	int	size;
	int	i;

	size = arr_len(array);
	i = 0;
	if (array)
	{
		while (i <= size)
		{
			free(array[i]);
			array[i] = NULL;
			i++;
		}
		free(array);
	}
	return (NULL);
}
