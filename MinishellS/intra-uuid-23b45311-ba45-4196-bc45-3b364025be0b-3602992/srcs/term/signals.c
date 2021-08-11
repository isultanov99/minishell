/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:20:17 by lkarliah          #+#    #+#             */
/*   Updated: 2021/08/07 21:20:17 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 0 - parent
** >0 - child
*/

void	main_input_re(void)
{
	g_data.history.flag = 0;
	if (g_data.history.command != NULL)
		free(g_data.history.command);
	g_data.history.command = NULL;
	g_data.history.command_print = 0;
	dlist_end();
}

void	hist_input_re(void)
{
	free(g_data.history.hist_end->content);
	g_data.history.hist_end->content = ft_strdup(g_data.history.hist_buf);
}

void	sig_int(int code)
{
	(void)code;
	if (g_data.sig_pid == 0)
	{
		write(1, "\n", 1);
		print_message();
		g_data.status = 1;
		if (g_data.history.flag == 1)
			hist_input_re();
		main_input_re();
	}
	if (g_data.sig_pid > 0)
		g_data.status = 130;
}

void	sig_quit(int code)
{
	(void)code;
	if (g_data.sig_pid == 0)
		ft_putstr_fd("\a", 1);
	if (g_data.sig_pid > 0)
		g_data.status = 131;
}

void	set_sig(void)
{
	signal(SIGINT, sig_int);
	signal(SIGQUIT, sig_quit);
}
