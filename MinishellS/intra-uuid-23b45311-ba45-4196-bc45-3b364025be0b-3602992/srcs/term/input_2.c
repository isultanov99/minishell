/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkarliah <lkarliah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 21:20:03 by lkarliah          #+#    #+#             */
/*   Updated: 2021/08/07 21:20:03 by lkarliah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_input(void)
{
	g_data.history.command = str_end(g_data.history.command);
	if (g_data.history.command[0] != '\0')
	{
		hist_add_str(g_data.history.command);
		parse_cmd(g_data.history.command);
	}
	g_data.history.command_print = 0;
	dlist_end();
}

void	hist_input(void)
{
	g_data.history.hist_end->content
		= str_end(g_data.history.hist_end->content);
	if (((char *)(g_data.history.hist_end->content))[0] != '\0')
	{
		hist_add_str(g_data.history.hist_end->content);
		parse_cmd(g_data.history.hist_end->content);
	}
	free(g_data.history.hist_end->content);
	g_data.history.hist_end->content = ft_strdup(g_data.history.hist_buf);
	dlist_end();
}

/*
**	обработка клавиши enter
**	здесь str_end используется для отсечения '\n'
*/

static void	kenter(void)
{
	if (g_data.history.flag == 0)
		main_input();
	if (g_data.history.flag == 1)
		hist_input();
	free(g_data.history.command);
	g_data.history.command = NULL;
	print_message();
	g_data.history.flag = 0;
}

void	control_characters(char *str)
{
	if (ft_strncmp(str, "\4", 1) == 0)
	{
		if (g_data.history.flag == 0 && g_data.history.command_print > 0)
			ft_putstr_fd("\a", 1);
		else
			if (g_data.history.flag == 1 && g_data.history.hist_print > 0)
				ft_putstr_fd("\a", 1);
		else
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
	}
	if (ft_strncmp(str, "\f", 1) == 0)
	{
		tputs(tgetstr("cl", 0), 1, output_func);
		print_message();
		if (g_data.history.flag == 0)
			ft_putstr_fd(g_data.history.command, 1);
		if (g_data.history.flag == 1)
			ft_putstr_fd(g_data.history.hist_end->content, 1);
	}
	if (ft_strncmp(str, "\n", 1) == 0)
		kenter();
}
