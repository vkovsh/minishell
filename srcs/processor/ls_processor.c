#include "minishell.h"

void		ls_processor(SHELL *s, CMD *c)
{
	pid_t	c_pid;
	char	*ls_bin_path;

	ls_bin_path = ft_strjoin(s->bin_path, "ls");
	c->cmd_status = EXEC_SUCCESS;
	c_pid = fork();
	if (c_pid == 0)
	{
		if ((execve(ls_bin_path, c->cmd_args, NULL) == -1))
			c->cmd_status = EXEC_FAIL;
	}
	else
	{
		wait(NULL);
		ft_strdel(&ls_bin_path);
	}
}