#include "minishell.h"
#include "libft.h"
#include "retcode.h"
#include <unistd.h>
#include "shellinfo.h"

t_retcode	echo_processor(shell *s, cmd *c)
{
	size_t	length;
	char	**begin;

	begin = c->cmd_args;
	while ((*(++c->cmd_args)))
	{
		(void)s;
		length = ft_strlen(*c->cmd_args);
		write(1, *c->cmd_args, length);
		if (*(c->cmd_args + 1))
			write(1, " ", 1);
	}
	write(1, "\n", 1);
	c->cmd_args = begin;
	return (RC_SUCCESS);
}