#include "minishell.h"
#include "ft_printf.h"

t_retcode	clear_processor(shell *s, cmd *c)
{
	const char clear_code[] = "\e[1;1H\e[2J";
	
	(void)s;
	(void)c;
	ft_printf("%s", clear_code);
	return (RC_SUCCESS);
}