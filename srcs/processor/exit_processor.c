#include "minishell.h"

void	exit_processor(shell *s, cmd *c)
{
	c->cmd_status = EXEC_SUCCESS;
	s->shell_exit = true;
}