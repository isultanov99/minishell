/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpablo <cpablo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 22:13:45 by cpablo            #+#    #+#             */
/*   Updated: 2021/04/29 22:29:04 by cpablo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	gnl_free(char **line)
{
	free(*line);
	*line = NULL;
}

void	gnl_tmp(t_gnl *gnl, char **line)
{
	gnl->tmp = *line;
	*line = ft_strjoin(*line, gnl->buf);
	free(gnl->tmp);
}
