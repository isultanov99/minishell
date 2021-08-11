#include "../includes/minishell.h"

void	pwd(void)
{
	char *pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	pwd = NULL;
}

void	cd(const char *cd)
{
	chdir(cd);
}

void	echo(char **line)
{
	int i;

	i = 1;
	while (line[i] != NULL)
	{
		printf("%s", line[i]);
		i++;
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	char **command_line;

	command_line = 'авыаыа';
	cd("/Users/arsenyburov/Coding/");
	pwd();
	echo(&command_line[0]);
	return (0);
}