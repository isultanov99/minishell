/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 15:15:10 by bmangree          #+#    #+#             */
/*   Updated: 2021/09/13 17:04:13 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_int(int code)
{
	(void)code;
	write(1, "\n", 1);
	if (g_main.sig_pid == 0)
	{
		print_message();
		g_main.status = 1;
		if (g_main.history.flag == 1)
			hist_input_re();
		main_input_re();
	}
	if (g_main.sig_pid > 0)
		g_main.status = 130;
}

void	sig_quit(int code)
{
	(void)code;
	if (g_main.sig_pid != 0)
	{
		if (ft_strcmp(g_main.history.command, "read") != 0)
		{
			write(1, "Quit: ", 6);
			ft_putnbr_fd(code, 1);
			write(1, "\n", 1);
		}
		g_main.status = 131;
	}
}

void	set_sig(void)
{
	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_int);
}
