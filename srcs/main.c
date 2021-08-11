#include "../includes/minishell.h"

int	count_words(char* readline)
{
	int i;
	int wordcount;

	i = 0;
	wordcount = 0;
	while (readline[i] != '\n')
	{
		if (readline[i] != ' ' && (readline[i+1] == ' ' || readline[i+1] == '\n'))
			wordcount++;
		i++;
	}
	return (wordcount);
}

int	main(int argc, char **argv, char **env)
{
	char* cwd;
	char* line;

	signal(SIGQUIT, )
	while (1)
	{
		cwd = ft_calloc(1024, 1);
		getcwd(cwd, 1024);
		write(1, "\033[1;34m", ft_strlen("\033[1;34m"));
		line = readline(cwd);
		write(1, "\033[0m", ft_strlen("\033[0m"));
		add_history(line);
		free(line);
		free(cwd);
	}
	return (0);
}
