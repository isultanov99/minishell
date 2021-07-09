/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 00:37:41 by bmangree          #+#    #+#             */
/*   Updated: 2020/11/20 19:17:37 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fill(int num, char *arr, int d_num, int ng_fl)
{
	arr[d_num] = '\0';
	if (num == -2147483648)
	{
		num /= 10;
		arr[--d_num] = '8';
	}
	num *= ng_fl;
	while (d_num--)
	{
		arr[d_num] = (num % 10) + 48;
		num /= 10;
	}
	if (ng_fl == -1)
		arr[0] = '-';
	return (arr);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		d_num;
	int		num;
	int		ng_fl;

	ng_fl = 1;
	d_num = 1;
	num = n;
	if ((num) < 0)
	{
		d_num++;
		ng_fl *= -1;
	}
	n /= 10;
	while (n)
	{
		d_num++;
		n /= 10;
	}
	arr = malloc(d_num + 1);
	if (!(arr))
		return (NULL);
	return (ft_fill(num, arr, d_num, ng_fl));
}
