#include "minishell.h"

static void	change_exec_dir(shell *s, const char *cd_path)
{
	char	buf[PATH_MAX];

	chdir(cd_path);
	ft_strdel(&s->current_proc_path);
	s->current_proc_path =	ft_strdup(getcwd(buf, PATH_MAX));
	delete_string(s->prompt);
	s->prompt =	create_prompt(s->current_proc_path);
}

void		cd_processor(shell *s, cmd *c)
{
	char	*cd_path;
	
	c->cmd_status = EXEC_SUCCESS;
	if (c->cmd_args[1] == NULL)
	{
		cd_path = FIND(s->environ, "HOME", 4);
		change_exec_dir(s, cd_path);
	}
	else if (access(c->cmd_args[1], F_OK | X_OK) == -1)
		ft_printf("'%s' permission denied\n", c->cmd_args[1]);
	else
	{
		cd_path = *(c->cmd_args + 1);
		change_exec_dir(s, cd_path);
	}
}