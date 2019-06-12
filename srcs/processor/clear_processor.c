#include "minishell.h"
#include "ft_printf.h"

void	clear_processor(shell *s, cmd *c)
{
	const char clear_code[] = "\e[1;1H\e[2J";
	(void)s;
	c->cmd_status = EXEC_SUCCESS;
	ft_printf("%s", clear_code);
}