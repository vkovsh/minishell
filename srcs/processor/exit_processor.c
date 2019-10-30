#include "minishell.h"

t_retcode	exit_processor(shell *s, cmd *c)
{
	(void)c;
	s->shell_exit = true;
	return (RC_SUCCESS);
}