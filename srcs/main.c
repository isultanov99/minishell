#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char* cwd;
	char* line;
	char* usernm;

	cwd = ft_calloc(1024, 1);
	getcwd(cwd, 1024);
	usernm = ft_strjoin(getenv("USER"),":");
	write(1, "\033[1;32m", ft_strlen("\033[1;31m"));
	write(1, usernm, ft_strlen(usernm));
	write(1, "\033[1;34m", ft_strlen("\033[1;34m"));
	write(1, cwd, ft_strlen(cwd));
	line = readline("\033[0m$ ");

	printf("%s", line);
	free(cwd);
	free(line);
	free(usernm);
	return (0);
}
