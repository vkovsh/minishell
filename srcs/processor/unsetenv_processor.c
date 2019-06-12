#include "minishell.h"
#include "ft_printf.h"

void	unsetenv_processor(shell *s, cmd *c)
{
	(void)s;
	ft_printf("CMD_NAME = %s\n", c->cmd_name);
	c->cmd_status = EXEC_SUCCESS;
}