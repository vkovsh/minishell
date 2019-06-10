#include "minishell.h"

void	pwd_processor(shell *s, cmd *c)
{
	(void)s;
	(void)c;
	c->cmd_status = EXEC_SUCCESS;
	ft_printf("%s\n", s->current_proc_path);
}