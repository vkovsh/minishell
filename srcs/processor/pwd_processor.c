#include "minishell.h"
#include "ft_printf.h"

t_retcode	pwd_processor(shell *s, cmd *c)
{
	(void)c;
	ft_printf("%s\n", s->current_proc_path);
	return (RC_SUCCESS);
}