/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 19:50:48 by cpablo            #+#    #+#             */
/*   Updated: 2020/11/11 19:50:50 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (((c >= 48) && (c <= 57)) || ((c >= 'A' && c <= 'Z') ||
	(c >= 'a' && c <= 'z')));
}
