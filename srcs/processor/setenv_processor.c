#include "minishell.h"

void	setenv_processor(shell *s, cmd *c)
{
	(void)s;
	ft_printf("CMD_NAME = %s\n", c->cmd_name);
	c->cmd_status = EXEC_SUCCESS;
}