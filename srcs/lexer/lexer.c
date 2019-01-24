#include "minishell.h"

char			**trim_cmds(char **split_cmds)
{
	char		*trash;
	char		**result = split_cmds;

	while (*split_cmds)
	{
		trash = *split_cmds;
		*split_cmds = ft_strtrim(*split_cmds);
		split_cmds++;
		ft_strdel(&trash);
	}
	return (result);
}

t_list			*lexer(const char *cmd_txt,
				t_processor	*processors)
{
	char		**split_cmds = NULL;
	t_list		*result = NULL;
	char		**trash;
	t_cmd		c;

	split_cmds = ft_strsplit(cmd_txt, ';');
	split_cmds = trim_cmds(split_cmds);
	trash = split_cmds;
	while (*split_cmds)
	{
		c = create_command(*split_cmds,	processors);
		ft_lstadd(&result, ft_lstnew(&c, sizeof(t_cmd)));
		split_cmds++;
	}
	delete_args_array(trash);
	ft_lstrev(&result);
	return (result);
}