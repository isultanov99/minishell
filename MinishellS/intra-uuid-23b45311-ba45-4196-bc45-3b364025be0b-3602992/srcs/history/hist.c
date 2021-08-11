/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:19:53 by lkarliah          #+#    #+#             */
/*   Updated: 2021/08/07 21:19:53 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	создаёт историю и сохраняет дескриптор
*/

void	hist_create(void)
{
	char	*path;
	char	*file_name;
	char	*str;

	path = env_get_var("HOME");
	file_name = ft_strjoin(path, "/.minishell_history");
	free(path);
	g_data.history.hist_fd
		= open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	close(g_data.history.hist_fd);
	g_data.history.hist_start = NULL;
	g_data.history.hist_fd = open(file_name, O_RDONLY);
	while (get_next_line(g_data.history.hist_fd, &str) > 0)
	{
		dlist_add_back(&(g_data.history.hist_start), dlist_new(ft_strdup(str)));
		free(str);
	}
	free(str);
	close(g_data.history.hist_fd);
	g_data.history.hist_fd
		= open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	free(file_name);
	dlist_end();
	g_data.history.flag = 0;
}

/*
**	добавляет введённую строку в историю
*/

void	hist_add_str(char *str)
{
	char	str_size;

	str_size = ft_strlen(str);
	write(g_data.history.hist_fd, str, str_size);
	write(g_data.history.hist_fd, "\n", 1);
	dlist_add_back(&(g_data.history.hist_start), dlist_new(ft_strdup(str)));
}
