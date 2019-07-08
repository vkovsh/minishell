#include "minishell.h"
#include "stdlib.h"
#include "ft_printf.h"

static uint8_t set_flag_mask(char f)
{
	t_envflags e;
	const uint8_t masks[ENV_TOTAL] = MASKS;

	e = ENV_UNDEFINED;
	while (++e < ENV_TOTAL)
		if (f == ENV_FLAGS_LITERALS[e])
			return (masks[e]);
	return (0);
}

void env_processor(shell *s, cmd *c)
{
	uint8_t			flags;
	int				i;
	int				j;
	char			*cmd_name;
	t_dictionary	*environ;
	char			*value;
	char			**key_value;
	t_node			item;
	
	flags = 0;
	cmd_name = NULL;
	i = 0;
	while (c->cmd_args[++i] && *(c->cmd_args[i]) == '-')
	{
		j = 1;
		while (c->cmd_args[i][j])
		{
			flags |= set_flag_mask(c->cmd_args[i][j++]);
		}
	}
	environ = s->environ->clone(s->environ);
	while (c->cmd_args[i] != NULL)
	{
		value = ft_strchr(c->cmd_args[i], '=');
		if (value != NULL)
		{
			key_value = ft_strsplit(c->cmd_args[i], '=');
			item = ITEM(key_value[0],
						ft_strlen(key_value[0]) + 1,
						key_value[1],
						ft_strlen(key_value[1]) + 1);
			INSERT(environ, &item);
			delete_args_array(key_value);
		}
		else
		{
			
		}
		
	}
}