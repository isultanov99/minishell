/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 19:10:26 by bmangree          #+#    #+#             */
/*   Updated: 2021/09/17 19:10:27 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	keypressup(void)
{
	if (g_main.hist.h_end == 0)
		ft_putstr_fd("\a", 1);
	if (g_main.hist.h_end)
	{
		tputs(tgetstr("rc", 0), 1, output_func);
		tputs(tgetstr("cd", 0), 1, output_func);
		if (g_main.hist.h_end->prev == 0 && g_main.hist.flag == 1)
			ft_putstr_fd("\a", 1);
		if (g_main.hist.h_end->prev && g_main.hist.flag == 1)
			g_main.hist.h_end = g_main.hist.h_end->prev;
		g_main.hist.flag = 1;
		ft_putstr_fd(g_main.hist.h_end->content, 1);
		g_main.hist.h_print = ft_strlen(g_main.hist.h_end->content);
		if (g_main.hist.h_buf)
			free(g_main.hist.h_buf);
		g_main.hist.h_buf = ft_strdup(g_main.hist.h_end->content);
	}
}

void	keypressdown(void)
{
	tputs(tgetstr("rc", 0), 1, output_func);
	tputs(tgetstr("cd", 0), 1, output_func);
	if (g_main.hist.h_end && g_main.hist.h_end->next)
	{
		g_main.hist.h_end = g_main.hist.h_end->next;
		ft_putstr_fd(g_main.hist.h_end->content, 1);
		g_main.hist.h_print = ft_strlen(g_main.hist.h_end->content);
		if (g_main.hist.h_buf)
			free(g_main.hist.h_buf);
		g_main.hist.h_buf = ft_strdup(g_main.hist.h_end->content);
	}
	else
	{
		if (g_main.hist.flag == 0)
			ft_putstr_fd("\a", 1);
		g_main.hist.flag = 0;
		ft_putstr_fd(g_main.hist.command, 1);
	}
}

void	keypressback(void)
{
	if (g_main.hist.command_print <= 0 && g_main.hist.h_print <= 0)
		ft_putstr_fd("\a", 1);
	if (g_main.hist.command_print > 0 && g_main.hist.flag == 0)
	{
		tputs(tgetstr("le", 0), 1, output_func);
		tputs(tgetstr("dc", 0), 1, output_func);
		g_main.hist.command_print--;
		g_main.hist.command = str_end(g_main.hist.command);
	}
	if (g_main.hist.h_print > 0 && g_main.hist.flag == 1)
	{
		tputs(tgetstr("le", 0), 1, output_func);
		tputs(tgetstr("dc", 0), 1, output_func);
		g_main.hist.h_print--;
		g_main.hist.h_end->content
			= str_end(g_main.hist.h_end->content);
	}
}

void	keypressenter(void)
{
	if (g_main.hist.flag == 0)
		main_input();
	if (g_main.hist.flag == 1)
		h_input();
	free(g_main.hist.command);
	g_main.hist.command = NULL;
	print_msg();
	g_main.hist.flag = 0;
}

int	key_hander(char *key)
{
	if (ft_strncmp(key, "\e[A", 3) == 0)
	{
		keypressup();
		return (1);
	}
	if (ft_strncmp(key, "\e[B", 3) == 0)
	{
		keypressdown();
		return (2);
	}
	if (ft_strncmp(key, "\177", 1) == 0)
	{
		keypressback();
		return (5);
	}
	if (ft_strncmp(key, "\e[C", 1) == 0)
		return (3);
	if (ft_strncmp(key, "\e[D", 1) == 0)
		return (4);
	return (0);
}
