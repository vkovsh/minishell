#include "minishell.h"

void	pwd_processor(SHELL *s, CMD *c)
{
	c->cmd_status = EXEC_SUCCESS;
	ft_printf("%s\n", s->current_proc_path);
}