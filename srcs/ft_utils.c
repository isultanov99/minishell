#include "../includes/minishell.h"

void	add_heredoc(char *end, int heredoc_fd)
{
	char	*input;

	input = "\0";
	while (1)
	{
		input = readline("> ");
		if (input == 0)
		{
			ft_putstr_fd("\b\b", 2);
			exit(0);
		}
		if (ft_strcmp(input, end))
		{
			ft_putstr_fd(input, heredoc_fd);
			ft_putstr_fd("\n", heredoc_fd);
		}
		else
			exit(0);
	}
}

int	get_input(char *stop, int heredoc_fd)
{
	int	status;

	reset_term();
	g_main.sig_pid = fork();
	if (g_main.sig_pid == 0)
	{
		signal(SIGINT, &sigint_handler);
		signal(SIGQUIT, &sigquit_handler);
		add_heredoc(stop, heredoc_fd);
	}
	else if (g_main.sig_pid < 0)
		exit(1);
	wait(&status);
	g_main.sig_pid = 0;
	close(heredoc_fd);
	status = WTERMSIG(status);
	return (status);
}

int	n_is_print(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_isprint(str[i]) == 0 && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*str_end(char *str)
{
	char	*new_str;
	int		str_size;
	int		i;

	if (str == 0)
		return (ft_strdup(""));
	str_size = ft_strlen(str);
	new_str = (char *)malloc(sizeof(char) * str_size);
	i = 0;
	while (str[i + 1] != '\0')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

char	*get_command(char *str, char *add)
{
	char	*command;

	command = ft_strjoin(str, add);
	if (command == 0)
		command = ft_strdup(add);
	else
		free(str);
	free(add);
	return (command);
}
