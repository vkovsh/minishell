#include "minishell.h"

static void	print(void *k, size_t k_size,
			void *v, size_t v_size)
{
	(void)k_size;
	(void)v_size;
	ft_printf("%s=%s\n", k, v);
}

void		env_processor(SHELL *s, CMD *c)
{
	if (!c->cmd_args[1])
		ft_bintree_infix_traverse(&s->environ, print);
	c->cmd_status = EXEC_SUCCESS;
}