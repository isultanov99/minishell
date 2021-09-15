/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmangree <bmangree@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 20:25:00 by bmangree          #+#    #+#             */
/*   Updated: 2021/09/16 00:31:28 by bmangree         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	main_input(void)
{
	g_main.history.command = str_end(g_main.history.command);
	if (g_main.history.command[0] != '\0')
	{
		hist_add_str(g_main.history.command);
		parse_cmd(g_main.history.command);
	}
	g_main.history.command_print = 0;
	dlist_end();
}

void	hist_input(void)
{
	g_main.history.hist_end->content
		= str_end(g_main.history.hist_end->content);
	if (((char *)(g_main.history.hist_end->content))[0] != '\0')
	{
		hist_add_str(g_main.history.hist_end->content);
		parse_cmd(g_main.history.hist_end->content);
	}
	free(g_main.history.hist_end->content);
	g_main.history.hist_end->content = ft_strdup(g_main.history.hist_buf);
	dlist_end();
}

void	main_inp(void)
{
	g_main.history.flag = 0;
	if (g_main.history.command != NULL)
		free(g_main.history.command);
	g_main.history.command = NULL;
	g_main.history.command_print = 0;
	dlist_end();
}

void	hist_inp(void)
{
	free(g_main.history.hist_end->content);
	g_main.history.hist_end->content = ft_strdup(g_main.history.hist_buf);
}

void	input(void)
{
	int		i;
	char	buf[4];

	print_message();
	g_main.history.command_print = 0;
	g_main.history.command = NULL;
	g_main.history.hist_buf = NULL;
	while (1)
	{
		i = read(0, buf, 3);
		buf[i] = '\0';
		if (!keys(buf) && n_is_print(buf) == 0)
		{
			write(1, buf, i);
			hist_or_command(buf);
		}
		control_characters(buf);
	}
	free(g_main.history.command);
	free(g_main.history.hist_buf);
}
