#include "minishell.h"
#include "stdlib.h"
#include "ft_printf.h"

static void		print_node_default(t_node *node, void *out)
{
	(void)out;
	ft_printf("%s=%s\n", node->key, node->value);
}

static void		print_node_zero(t_node *node, void *out)
{
	(void)out;
	ft_printf("%s=%s;", node->key, node->value);
}

static uint8_t	set_flag_mask(char f)
{
	t_envflags e;
	const uint8_t masks[ENV_TOTAL] = MASKS;

	e = ENV_UNDEFINED;
	while (++e < ENV_TOTAL)
	{
		if (f == ENV_FLAGS_LITERALS[e])
		{
			return (masks[e]);
		}
	}
	return (0);
}

static void	del_node(t_node *item, t_del_key del_k, t_del_value del_v)
{
	del_k(item->key);
	del_v(item->value);
}

void env_processor(shell *s, cmd *c)
{
	uint8_t			flags;
	uint8_t			flag;
	int				i;
	int				j;
	char			*cmd_txt;
	t_dictionary	*environ;
	char			*value;
	char			**key_value;
	t_node			item;
	char			**environ_array;
	t_cmd			sub_cmd;
	
	flags = 0;
	cmd_txt = NULL;
	i = 0;
	while (c->cmd_args[++i] && *(c->cmd_args[i]) == '-')
	{
		j = 1;
		while (c->cmd_args[i][j])
		{
			flag = set_flag_mask(c->cmd_args[i][j++]);
			if (flag == 0)
			{
				ft_printf("env: invalid option -- '%c'\n", c->cmd_args[i][j - 1]);
				return ;
			}
			flags |= flag;
		}
	}
	environ_array = NULL;
	environ = NULL;
	if ((flags & ENV_I_M) != 0)
	{
		const t_del del_struct = (t_del){free, free, del_node};
		init_dictionary(&environ, ft_memcmp, &del_struct);
	}
	else
	{
		environ = s->environ->clone(s->environ);
	}
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
		else if (cmd_txt == NULL)
		{
			cmd_txt = ft_strdup(c->cmd_args[i]);
		}
		else
		{
			cmd_txt = ft_strjoin_free(cmd_txt, " ", TRUE, FALSE);
			cmd_txt = ft_strjoin_free(cmd_txt, c->cmd_args[i], TRUE, FALSE);
		}
		i++;
	}
	if (cmd_txt != NULL)
	{
		environ_array = (char **)environ->data(environ);
		sub_cmd = create_command(cmd_txt, s);
		char *trash = sub_cmd.cmd_name;
		char **pathes = ft_strsplit(FIND(environ, "PATH", 4), ':');
		if (pathes == NULL)
		{
			pathes = ft_strsplit(FIND(s->environ, "PATH", 4), ':');
		}
		sub_cmd.cmd_name = exec_bin_path(sub_cmd.cmd_name, pathes);
		if (sub_cmd.cmd_name == NULL)
		{
			sub_cmd.cmd_name = trash;
		}
		else
		{
			ft_strdel(&trash);
		}
		delete_args_array(pathes);
		t_list *command = NULL;
		ft_lstadd(&command, ft_lstnew(&sub_cmd, sizeof(sub_cmd)));
		char** buf1 = s->env_array;
		t_dictionary *dict = s->environ;
		s->environ = environ;
		s->env_array = environ_array;
		exec(s, command);
		s->env_array = buf1;
		s->environ = dict;
	}
	else
	{
		// char delim;
		if (flags == 0 || (flags & ENV_I_M) != 0)
		{
			if (environ->array != NULL)
			{
				ft_bintree_infix_traverse(&(environ->array), print_node_default, NULL);
			}
			// delim = '\n';
		}
		else if ((flags & ENV_ZERO_M) != 0)
		{
			if (environ->array != NULL)
			{
				ft_bintree_infix_traverse(&(environ->array), print_node_zero, NULL);
			}
			// delim = ';';
		}
		// ft_bintree_infix_traverse(&(environ->array), print_node, &delim);
	}
	if (environ != NULL)
	{
		CLEAR(environ);
		free(environ);
	}
}