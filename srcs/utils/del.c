#include "minishell.h"

void		delete_args_array(char **arr)
{
	char	**trash;

	trash = arr;
	while (*arr)
		ft_strdel(arr++);
	free(trash);
}

void		del_cmd_entry(void *content,
			size_t content_size)
{
	t_cmd	*c;

	if (!content)
		return ;
	(void)content_size;
	c = (t_cmd *)content;
	ft_strdel(&c->cmd_name);
	if (c->cmd_args)
		delete_args_array(c->cmd_args);
	free(c);
}

void	del_tree_node(void *k, size_t k_s,
		void *v, size_t v_s)
{
	free(k);
	free(v);
	(void)k_s;
	(void)v_s;
}

void	delete_shellinfo(t_shellinfo *s)
{
	ft_strdel(&s->current_proc_path);
	ft_strdel(&s->init_proc_path);
	ft_strdel(&s->bin_path);
	delete_string(s->prompt);
	ft_lstdel(&(s->cmd_history), del_cmd_entry);
	CLEAR(s->environ);
	free(s->environ);
	free(s->env_array);
}