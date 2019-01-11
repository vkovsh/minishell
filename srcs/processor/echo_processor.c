#include "minishell.h"

void		echo_processor(SHELL *s, CMD *c)
{
	size_t	length;
	char	*key;
	char	**begin;

	begin = c->cmd_args;
	while ((*(++c->cmd_args)))
	{
		length = ft_strlen(*c->cmd_args);
		if (**c->cmd_args == '\042' && *(*c->cmd_args + length - 1) == '\042')
			write(1, ((*c->cmd_args) + 1), length - 2);
		else if (**c->cmd_args == '$')
		{
			key = *c->cmd_args + 1;
			ft_printf("%s", ft_bintree_find((t_bintree **)&s->environ,
				key, ft_strlen(key), ft_memcmp)->value);
		}
		else
			write(1, *c->cmd_args, length);
		if (*(c->cmd_args + 1))
			write(1, " ", 1);
	}
	write(1, "\n", 1);
	c->cmd_args = begin;
}