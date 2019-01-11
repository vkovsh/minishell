#include "minishell.h"

void	clear_processor(SHELL *s, CMD *c)
{
	(void)s;
	c->cmd_status = EXEC_SUCCESS;
	ft_printf("%s", CLEAR_SCREEN_ANSI);
}