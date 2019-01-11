#include "minishell.h"

void	unsetenv_processor(SHELL *s, CMD *c)
{
	(void)s;
	ft_printf("CMD_NAME = %s\n", c->cmd_name);
	c->cmd_status = EXEC_SUCCESS;
}