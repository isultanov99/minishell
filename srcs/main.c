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
	h_create();
	input();
	dlist_free(g_main.hist.h_start);
	close(g_main.hist.h_fd);
	list_free(g_main.env);
}
