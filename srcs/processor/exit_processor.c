#include "minishell.h"

void	exit_processor(SHELL *s, CMD *c)
{
	c->cmd_status = EXEC_SUCCESS;
	s->shell_exit = true;
}