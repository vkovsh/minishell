#include <termcap.h>
#include <stdlib.h>
#include "minishell.h"
#include <stdio.h>
#include "retcode.h"
#include <unistd.h>

// static char term_buffer[2048];

static char g_buf[128];
static char *g_buf_addr = g_buf;

char    *g_clear_str;
char    *g_goto_str;
char    *g_standout_begin_str;
char    *g_standout_end_str;
char    *g_key_up_str;
char    *g_key_down_str;
char    *g_key_left_str;
char    *g_key_right_str;

static t_retcode    init_terminal_str(void)
{
    g_clear_str = tgetstr("cl", &g_buf_addr);
    if (g_clear_str == NULL)
    {
        return (RC_ERR_TERM_NO_CL);
    }
    g_goto_str = tgetstr("cm", &g_buf_addr);
    if (g_goto_str == NULL)
    {
        return (RC_ERR_TERM_NO_CM);
    }
	g_standout_begin_str = tgetstr("so", &g_buf_addr);
    if (g_standout_begin_str == NULL)
    {
        return (RC_ERR_TERM_NO_SO);
    }
	g_standout_end_str = tgetstr("se", &g_buf_addr);
    if (g_standout_end_str == NULL)
    {
        return (RC_ERR_TERM_NO_SE);
    }
    g_key_up_str = tgetstr("ku", &g_buf_addr);
    if (g_key_up_str == NULL)
    {
        return (RC_ERR_TERM_NO_KU);
    }
    g_key_down_str = tgetstr("kd", &g_buf_addr);
    if (g_key_down_str == NULL)
    {
        return (RC_ERR_TERM_NO_KD);
    }
    g_key_left_str = tgetstr("kl", &g_buf_addr);
    if (g_key_left_str == NULL)
    {
        return (RC_ERR_TERM_NO_KL);
    }
    g_key_right_str = tgetstr("kr", &g_buf_addr);
    if (g_key_right_str == NULL)
    {
        return (RC_ERR_TERM_NO_KR);
    }
    return (RC_SUCCESS);
}

int	rl_print_key(int s)
{
	write(1, &s, 1);
	return 1;
}

t_retcode   init_terminal_data(void)
{
    int success;
    t_retcode   result;
    const char *termtype = getenv("TERM");
	char bp[1024];

    if (termtype == NULL)
        return (RC_ERR_TERM_NOT_SET);
    result = RC_ERR; 
    success = tgetent(bp, termtype);
    if (success < 0)
        return (RC_ERR_TERMINFO_DB_ACCESS);
    if (success == 0)
        return (RC_ERR_TERMTYPE_UNDEFINED);
    result = init_terminal_str();
	// tputs(tgoto(g_goto_str, 10, 1), 0, &rl_print_key);
    // printf("%s%s%s\n", g_standout_begin_str, "TEST", g_standout_end_str);
    return (result);
}