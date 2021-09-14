/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:33:46 by cpablo            #+#    #+#             */
/*   Updated: 2021/09/14 14:33:46 by cpablo           ###   ########.fr       */
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
