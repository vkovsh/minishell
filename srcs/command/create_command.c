#include "minishell.h"

static t_cmdnums	init_cmd_id(const char *cmd)
{
	t_cmdnums		tmp;
	const char	*cmds[CMD_TOTAL] = CMDS;

	tmp = INIT;
	while (++tmp < CMD_TOTAL)
		if (!ft_strcmp(cmds[tmp], cmd))
			return (tmp);
	return (ARBITRARY_ID);
}

t_cmd				create_command(const char *cmd_txt,
					t_processor *ptable)
{
	char			**split_cmd;
	t_cmd			new_cmd;
	t_cmdnums		cmd_id;

	split_cmd = ft_strsplit(cmd_txt, ' ');
	cmd_id = init_cmd_id(split_cmd[0]);
	new_cmd.cmd_id = cmd_id;
	new_cmd.cmd_name = ft_strdup(split_cmd[0]);
	new_cmd.cmd_status = EXEC_READY;
	new_cmd.cmd_args = split_cmd;
	new_cmd.cmd_processor = ptable[new_cmd.cmd_id];
	return (new_cmd);
}