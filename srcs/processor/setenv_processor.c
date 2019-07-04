#include "minishell.h"
#include "ft_printf.h"

static void	override_envarray(shell *s)
{
	delete_args_array(s->env_array);
	s->env_array = (char **)s->environ->data(s->environ);
}

void		setenv_processor(shell *s, cmd *c)
{
	char	*name;
	char	*value;
	t_node	node;

	name = (c->cmd_args_count >= 2) ? c->cmd_args[1] : NULL;
	value = (c->cmd_args_count >= 3) ? c->cmd_args[2] : NULL;
	if (name != NULL)
	{
		if (value != NULL)
		{
			node = ITEM(name, ft_strlen(name) + 1, value, ft_strlen(value) + 1);
		}
		else
		{
			node = ITEM(name, ft_strlen(name) + 1, "", 1);
		}
		INSERT(s->environ, &node);
		override_envarray(s);
		c->cmd_status = EXEC_SUCCESS;
	}
	else
	{
		ft_printf("Usage: setenv <NAME> <VALUE>\n");
		c->cmd_status = EXEC_FAIL;
	}
}