#include "../includes/minishell.h"

void	sig_quit(int code)
{
	if (g_signal.pid != 0)
	{
		ft_putstr_fd("Quit: ", 1);
		ft_putnbr_fd(code, 1);
		ft_putstr_fd("\n", 1);
		g_signal.status = 131;
	}
	g_signal.quit = 1;
}
