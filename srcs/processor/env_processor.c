#include "minishell.h"
/*
static void			print(void *k, size_t k_size,
						void *v, size_t v_size)
{
	(void)k_size;
	(void)v_size;
	ft_printf("%s=%s\n", k, v);
}*/

static uint8_t		set_flag_mask(char f)
{
	t_envflags		e;
	const uint8_t	masks[ENV_TOTAL] = MASKS;

	e = ENV_UNDEFINED;
	while (++e < ENV_TOTAL)
		if (f == ENV_FLAGS_LITERALS[e])
			return (masks[e]);
	return (0);
}

void				env_processor(SHELL *s, CMD *c)
{
	(void)s;
	uint8_t			flags;
	int				i;
	int				j;
	char			*cmd_name;
	char			**cmd_args;
	//char			**cmd_environ;

	flags = 0;
	cmd_name = NULL;
	cmd_args = NULL;
	//if (!c->cmd_args[1])
	//	ft_bintree_infix_traverse(&s->environ, print);
	//else
	//{
	i = 0;
	while (*c->cmd_args[++i] == '-')
	{
		j = 1;
		while (c->cmd_args[i][j])
			flags |= set_flag_mask(c->cmd_args[i][j++]);
	}
	if (c->cmd_args[i])
		cmd_name = c->cmd_args[i++];
	cmd_args = &c->cmd_args[i];
	//if (flags & ENV_I_M)
	//	cmd_environ = NULL;
	(void)cmd_name;
	(void)cmd_args;
	//}
	c->cmd_status = EXEC_SUCCESS;
}