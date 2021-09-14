#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_main.status = 0;
	g_main.sig_pid = 0;
	set_sig();
	tcgetattr(0, &g_main.termset);
	setup_term();
	tputs(tgetstr("cl", 0), 1, output_func);
	env_get(envp);
	shlvl_set();
	hist_create();
	input();
	dlist_free(g_main.history.hist_start);
	close(g_main.history.hist_fd);
	env_free(g_main.env);
}
