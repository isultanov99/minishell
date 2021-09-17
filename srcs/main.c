#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	g_main.sig_pid = 0;
	g_main.status = 0;
	(void)argv;
	(void)argc;
	set_signal();
	tcgetattr(0, &g_main.termset);
	set_term();
	tputs(tgetstr("cl", 0), 1, output_func);
	env_get(envp);
	set_shlvl();
	h_create();
	input();
	dlist_free(g_main.hist.h_start);
	close(g_main.hist.h_fd);
	list_free(g_main.env);
}
