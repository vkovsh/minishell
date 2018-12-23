#include "minishell.h"

t_list			*lexer(t_string *command)
{
	t_cmdnums	i;
	char		*cmd_upper;
	const char	*cmds[CMD_TOTAL] = CMDS;

	i = UNDEFINED;
	cmd_upper = ft_strtoupper(command->str);
	while (++i < CMD_TOTAL)
		if (!ft_strcmp(cmd_upper, cmds[i]))
		{
			ft_strdel(&cmd_upper);
			return (NULL);
		}
	ft_strdel(&cmd_upper);
	return (NULL);
}