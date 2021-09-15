#include "../includes/minishell.h"

void	hist_create(void)
{
	char	*path;
	char	*file_name;
	char	*str;

	path = env_get_var("HOME");
	file_name = ft_strjoin(path, "/.minishell_history");
	free(path);
	g_main.history.hist_fd
		= open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	close(g_main.history.hist_fd);
	g_main.history.hist_start = NULL;
	g_main.history.hist_fd = open(file_name, O_RDONLY);
	while (get_next_line(g_main.history.hist_fd, &str) > 0)
	{
		dlist_add_back(&(g_main.history.hist_start), dlist_new(ft_strdup(str)));
		free(str);
	}
	free(str);
	close(g_main.history.hist_fd);
	g_main.history.hist_fd
		= open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
	free(file_name);
	dlist_end();
	g_main.history.flag = 0;
}

void	hist_add_str(char *str)
{
	char	str_size;

	str_size = ft_strlen(str);
	write(g_main.history.hist_fd, str, str_size);
	write(g_main.history.hist_fd, "\n", 1);
	dlist_add_back(&(g_main.history.hist_start), dlist_new(ft_strdup(str)));
}

void	hist_or_command(char *buf)
{
	if (g_main.history.flag == 0)
	{
		g_main.history.command_print++;
		g_main.history.command
			= get_command(g_main.history.command, ft_strdup(buf));
	}
	if (g_main.history.flag == 1)
	{
		g_main.history.hist_print++;
		g_main.history.hist_end->content
			= get_command(g_main.history.hist_end->content, ft_strdup(buf));
	}
}

void	control_characters(char *str)
{
	if (ft_strncmp(str, "\4", 1) == 0)
	{
		if (g_main.history.flag == 0 && g_main.history.command_print > 0)
			ft_putstr_fd("\a", 1);
		else
			if (g_main.history.flag == 1 && g_main.history.hist_print > 0)
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
		if (g_main.history.flag == 0)
			ft_putstr_fd(g_main.history.command, 1);
		if (g_main.history.flag == 1)
			ft_putstr_fd(g_main.history.hist_end->content, 1);
	}
	if (ft_strncmp(str, "\n", 1) == 0)
		keypressenter();
}

void	home_dir(char *message)
{
	ft_putstr_fd("\033[1;36m", 1);
	ft_putstr_fd(message, 1);
	write(1, ": ", 2);
	ft_putstr_fd("\033[0m", 1);
	tputs(tgetstr("sc", 0), 1, output_func);
	free(message);
}