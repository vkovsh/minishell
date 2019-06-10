#include "minishell.h"

static t_cmdnums	init_cmd_id(const char *cmd)
{
	t_cmdnums		tmp;
	const char	*cmds[CMD_TOTAL] =
		{"clear", "pwd", "echo", "cd",
		"setenv", "unsetenv", "env", "exit",""};

	tmp = INIT;
	while (++tmp < CMD_TOTAL)
		if (!ft_strcmp(cmds[tmp], cmd))
			return (tmp);
	return (ARBITRARY_ID);
}

static void			procede_spec_args(char **split_cmd, shell *s)
{
	char			**it;
	char			*trash;
	size_t			len;

	it = split_cmd;
	while (*++it != NULL)
	{
		if (**it == '$')
		{
			trash = *it;
			*it = FIND(s->environ, *it + 1, ft_strlen(*it + 1));
			*it = ft_strdup(*it ? *it : "");
			ft_strdel(&trash);
		}
		else if (!ft_strcmp(*it, "~") || !ft_strcmp(*it, "~/"))
		{
			trash = *it;
			*it = ft_strdup(FIND(s->environ, "HOME", 4));
			ft_strdel(&trash);
		}
		else if (**it == '\042' || **it == '\047')
		{
			trash = *it;
			len = ft_strlen(*it);
			if (**it == (*it)[len - 1])
			{
				*it = ft_strnew(len - 1);
				ft_memmove(*it, trash + 1, len - 2);
				(*it)[len - 1] = '\0';

			}
			else
			{
				*it = ft_strdup("");
			}
			ft_strdel(&trash);
		}
	}
}

t_cmd				create_command(const char *cmd_txt, shell *s)
{
	char			**split_cmd;
	t_cmd			new_cmd;
	t_cmdnums		cmd_id;

	split_cmd = ft_strsplit(cmd_txt, ' ');
	procede_spec_args(split_cmd, s);
	cmd_id = init_cmd_id(split_cmd[0]);
	new_cmd.cmd_id = cmd_id;
	new_cmd.cmd_name = ft_strdup(split_cmd[0]);
	new_cmd.cmd_status = EXEC_READY;
	new_cmd.cmd_args = split_cmd;
	new_cmd.cmd_processor = s->processors[new_cmd.cmd_id];
	return (new_cmd);
}