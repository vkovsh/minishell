#include "minishell.h"
#include "ft_printf.h"

void		unsetenv_processor(shell *s, cmd *c)
{
	size_t	counter;
	void	*value;
	
	if (c->cmd_args_count > 1)
	{
		counter = 1;
		while (counter < c->cmd_args_count)
		{
			value = s->environ->find(s->environ,
								c->cmd_args[counter],
								ft_strlen(c->cmd_args[counter]));
			if (value != NULL)
			{
				s->environ->del_item(s->environ,
								c->cmd_args[counter],
								ft_strlen(c->cmd_args[counter]) + 1);
				ft_printf("'%s' removed\n", c->cmd_args[counter]);
			}
			else
			{
				ft_printf("'%s' key does not set\n", c->cmd_args[counter]);
			}
			counter++;
		}
		delete_args_array(s->env_array);
		s->env_array = (char **)s->environ->data(s->environ);
	}
	else
	{
		ft_printf("Usage: unsetenv ...\n");
	}
	c->cmd_status = EXEC_SUCCESS;
}