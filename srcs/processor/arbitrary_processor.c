#include "minishell.h"
#include "ft_printf.h"

void			arbitrary_processor(shell *s, cmd *c)
{
	char		**path;
	char		*exec_path;
	pid_t		pid;

	c->cmd_status = EXEC_SUCCESS;
	path = NULL;
	exec_path = NULL;
	c->cmd_status = EXEC_SUCCESS;
	path = ft_strsplit(FIND(s->environ, "PATH", 4), ':');
	if ((pid = fork()) == -1)
	{
		exit(EXEC_FAIL);
	}
	if (pid == 0)
	{
		if ((exec_path = exec_bin_path(c->cmd_name, path)))
		{
			execve(exec_path, c->cmd_args, s->env_array);
		}
		c->cmd_status = EXEC_FAIL;
		ft_printf("'%s' command is undefined\n", c->cmd_name);
		exit(0);
	}
	else
	{
		wait(NULL);
		if (exec_path && c->cmd_status == EXEC_SUCCESS)
			ft_strdel(&exec_path);
		if (path)
			delete_args_array(path);
	}
}