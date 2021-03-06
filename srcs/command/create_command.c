#include "minishell.h"
#include "ft_printf.h"
#include "shellinfo.h"
#include "dictionary.h"

static t_cmd_id	init_cmd_id(const char *cmd)
{
	t_cmd_id	tmp;
	const char	*cmds[CMD_TOTAL] =
				{"clear", "pwd", "echo", "cd",
				"setenv", "unsetenv", "env", "exit", ""};

	tmp = INIT;
	while (++tmp < CMD_TOTAL)
	{
		if (ft_strcmp(cmds[tmp], cmd) == 0)
		{
			return (tmp);
		}
	}
	return (ARBITRARY_ID);
}

static void		procede_spec_args(char **split_cmd, shell *s)
{
	char		**it;
	char		*trash;
	
	it = split_cmd;
	while (*++it != NULL)
	{
		char quot = '\"';
		char *quoted_begin_pos = ft_strchr(*it, quot);
		char *addition = NULL;
		while (quoted_begin_pos != NULL)
		{
			char *quoted_end_pos = ft_strchr(quoted_begin_pos + 1, quot);
			if (quoted_end_pos == NULL)
			{
				addition = ft_strdup("\n");
				char *line = NULL;
				ft_printf("> ");
				while (get_next_line(0, &line) == 1)
				{
					addition = ft_strjoin_free(addition, line, TRUE, FALSE);
					addition = ft_strjoin_free(addition, "\n", TRUE, FALSE);
					char *typed_quot_pos = NULL;
					if ((typed_quot_pos = ft_strchr(line, quot)) != NULL)
					{
						break;
					}
					ft_printf("> ");
				}
				ft_strdel(&line);
				line = NULL;	
			}
			if (quoted_end_pos)
				quoted_begin_pos = ft_strchr(quoted_end_pos + 1, quot);
			else
			{
				quoted_begin_pos = NULL;
			}
		}
		if (addition != NULL)
		{
			*it = ft_strjoin_free(*it, addition, TRUE, TRUE);
		}
		trash = *it;
		*it = ft_substrcut(*it, "\"");
		ft_strdel(&trash);

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
		// else if (**it == '\042' || **it == '\047')
		// {
		// 	trash = *it;
		// 	len = ft_strlen(*it);
		// 	if (len > 1 && **it == (*it)[len - 1])
		// 	{
		// 		*it = ft_strnew(len - 1);
		// 		ft_memmove(*it, trash + 1, len - 2);
		// 		(*it)[len - 1] = '\0';
		// 	}
		// 	else
		// 	{
		// 		*it = ft_strdup("");
		// 	}
		// 	ft_strdel(&trash);
		// }
	}
}

t_cmd			create_command(const char *cmd_txt, shell *s)
{
	char		**split_cmd;
	t_cmd		new_cmd;
	t_cmd_id	cmd_id;
	char		*space_delim_p;

	ft_memset(&new_cmd, 0, sizeof(new_cmd));
	new_cmd.cmd_args_count = 1;
	new_cmd.cmd_txt = ft_strdup(cmd_txt);
	space_delim_p = (char *)cmd_txt;
	while ((space_delim_p = ft_strchr(space_delim_p, ' ')) != NULL)
	{
		space_delim_p++;
		new_cmd.cmd_args_count++;
	}
	split_cmd = ft_strsplit(cmd_txt, ' ');
	procede_spec_args(split_cmd, s);
	cmd_id = init_cmd_id(split_cmd[0]);
	new_cmd.cmd_id = cmd_id;
	new_cmd.cmd_name = ft_strdup(split_cmd[0]);
	new_cmd.cmd_args = split_cmd;
	new_cmd.cmd_processor = s->processors[new_cmd.cmd_id];
	return (new_cmd);
}