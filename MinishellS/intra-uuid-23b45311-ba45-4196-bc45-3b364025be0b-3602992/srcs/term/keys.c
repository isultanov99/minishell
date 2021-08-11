/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:20:06 by lkarliah          #+#    #+#             */
/*   Updated: 2021/08/07 21:20:06 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kup(void)
{
	if (g_data.history.hist_end == NULL)
		ft_putstr_fd("\a", 1);
	if (g_data.history.hist_end)
	{
		tputs(tgetstr("rc", 0), 1, output_func);
		tputs(tgetstr("cd", 0), 1, output_func);
		if (g_data.history.hist_end->prev == NULL && g_data.history.flag == 1)
			ft_putstr_fd("\a", 1);
		if (g_data.history.hist_end->prev && g_data.history.flag == 1)
			g_data.history.hist_end = g_data.history.hist_end->prev;
		g_data.history.flag = 1;
		ft_putstr_fd(g_data.history.hist_end->content, 1);
		g_data.history.hist_print = ft_strlen(g_data.history.hist_end->content);
		if (g_data.history.hist_buf)
			free(g_data.history.hist_buf);
		g_data.history.hist_buf = ft_strdup(g_data.history.hist_end->content);
	}
}

void	kdown(void)
{
	tputs(tgetstr("rc", 0), 1, output_func);
	tputs(tgetstr("cd", 0), 1, output_func);
	if (g_data.history.hist_end && g_data.history.hist_end->next)
	{
		g_data.history.hist_end = g_data.history.hist_end->next;
		ft_putstr_fd(g_data.history.hist_end->content, 1);
		g_data.history.hist_print = ft_strlen(g_data.history.hist_end->content);
		if (g_data.history.hist_buf)
			free(g_data.history.hist_buf);
		g_data.history.hist_buf = ft_strdup(g_data.history.hist_end->content);
	}
	else
	{
		if (g_data.history.flag == 0)
			ft_putstr_fd("\a", 1);
		g_data.history.flag = 0;
		ft_putstr_fd(g_data.history.command, 1);
	}
}

void	kback(void)
{
	if (g_data.history.command_print <= 0 && g_data.history.hist_print <= 0)
		ft_putstr_fd("\a", 1);
	if (g_data.history.command_print > 0 && g_data.history.flag == 0)
	{
		tputs(tgetstr("le", 0), 1, output_func);
		tputs(tgetstr("dc", 0), 1, output_func);
		g_data.history.command_print--;
		g_data.history.command = str_end(g_data.history.command);
	}
	if (g_data.history.hist_print > 0 && g_data.history.flag == 1)
	{
		tputs(tgetstr("le", 0), 1, output_func);
		tputs(tgetstr("dc", 0), 1, output_func);
		g_data.history.hist_print--;
		g_data.history.hist_end->content
			= str_end(g_data.history.hist_end->content);
	}
}

int	keys(char *key)
{
	if (ft_strncmp(key, "\e[A", 3) == 0)
	{
		kup();
		return (1);
	}
	if (ft_strncmp(key, "\e[B", 3) == 0)
	{
		kdown();
		return (2);
	}
	if (ft_strncmp(key, "\177", 1) == 0)
	{
		kback();
		return (5);
	}
	if (ft_strncmp(key, "\e[C", 1) == 0)
		return (3);
	if (ft_strncmp(key, "\e[D", 1) == 0)
		return (4);
	return (0);
}
