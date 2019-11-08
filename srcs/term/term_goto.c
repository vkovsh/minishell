#include "minishell.h"
#include <stdlib.h>
#include <termcap.h>
#include <stdio.h>
#include "retcode.h"

static int32_t	rl_print_key(int32_t n)
{
	//return ((int32_t)write(STDIN_FILENO, &n, 1));
    return (n);
}

t_retcode   term_goto(int x, int y)
{
    char    *goto_cmd;

    goto_cmd = tgoto(g_goto_str, x, y);
    if (goto_cmd == NULL)
        return (RC_ERR_BAD_TGOTO);
    if (0 != tputs(goto_cmd, 0, &rl_print_key))
        return (RC_ERR_BAD_TPUTS);
    return (RC_SUCCESS);
}