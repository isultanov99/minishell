#include "../includes/minishell.h"

void	keypressup(void)
{
	if (g_main.history.hist_end == 0)
		ft_putstr_fd("\a", 1);
	if (g_main.history.hist_end)
	{
		tputs(tgetstr("rc", 0), 1, output_func);
		tputs(tgetstr("cd", 0), 1, output_func);
		if (g_main.history.hist_end->prev == 0 && g_main.history.flag == 1)
			ft_putstr_fd("\a", 1);
		if (g_main.history.hist_end->prev && g_main.history.flag == 1)
			g_main.history.hist_end = g_main.history.hist_end->prev;
		g_main.history.flag = 1;
		ft_putstr_fd(g_main.history.hist_end->content, 1);
		g_main.history.hist_print = ft_strlen(g_main.history.hist_end->content);
		if (g_main.history.hist_buf)
			free(g_main.history.hist_buf);
		g_main.history.hist_buf = ft_strdup(g_main.history.hist_end->content);
	}
}

void	keypressdown(void)
{
	tputs(tgetstr("rc", 0), 1, output_func);
	tputs(tgetstr("cd", 0), 1, output_func);
	if (g_main.history.hist_end && g_main.history.hist_end->next)
	{
		g_main.history.hist_end = g_main.history.hist_end->next;
		ft_putstr_fd(g_main.history.hist_end->content, 1);
		g_main.history.hist_print = ft_strlen(g_main.history.hist_end->content);
		if (g_main.history.hist_buf)
			free(g_main.history.hist_buf);
		g_main.history.hist_buf = ft_strdup(g_main.history.hist_end->content);
	}
	else
	{
		if (g_main.history.flag == 0)
			ft_putstr_fd("\a", 1);
		g_main.history.flag = 0;
		ft_putstr_fd(g_main.history.command, 1);
	}
}

void	keypressback(void)
{
	if (g_main.history.command_print <= 0 && g_main.history.hist_print <= 0)
		ft_putstr_fd("\a", 1);
	if (g_main.history.command_print > 0 && g_main.history.flag == 0)
	{
		tputs(tgetstr("le", 0), 1, output_func);
		tputs(tgetstr("dc", 0), 1, output_func);
		g_main.history.command_print--;
		g_main.history.command = str_end(g_main.history.command);
	}
	if (g_main.history.hist_print > 0 && g_main.history.flag == 1)
	{
		tputs(tgetstr("le", 0), 1, output_func);
		tputs(tgetstr("dc", 0), 1, output_func);
		g_main.history.hist_print--;
		g_main.history.hist_end->content
			= str_end(g_main.history.hist_end->content);
	}
}

int	keys(char *key)
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