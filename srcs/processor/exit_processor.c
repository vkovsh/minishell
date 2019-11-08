#include "minishell.h"
#include "retcode.h"
#include "shellinfo.h"

t_retcode	exit_processor(shell *s, cmd *c)
{
	(void)c;
	s->shell_exit = 1;
	return (RC_SUCCESS);
}