#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include "../libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_vars{
 char   **envp_copy;
 int    count_envp;
 int    save_std_in;
 int    save_std_out;
 int    count_pipe;
 int    count_command;
 int    index_pipe;
 int    count_redirect;
 int    count_call_pipe;
 int    flag_redirect;
 int    err_flag;
 int    err_flag_export;
 int    cd_flag;
 int    *arr_flags;
}    t_vars;
