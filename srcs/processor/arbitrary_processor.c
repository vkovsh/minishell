#include "minishell.h"
#include "ft_printf.h"

t_retcode		arbitrary_processor(shell *s, cmd *c)
{
	char		**path;
	char		*exec_path;
	pid_t		pid;

	path = NULL;
	exec_path = NULL;
	path = ft_strsplit(FIND(s->environ, "PATH", 4), ':');
	pid = fork();
	if (pid == -1)
	{
		exit(1);
	}
	if (pid == 0)
	{
		if ((exec_path = exec_bin_path(c->cmd_name, path)))
		{
			execve(exec_path, c->cmd_args, s->env_array);
		}
		ft_printf("'%s' command is undefined\n", c->cmd_name);
		exit(0);
	}
	else
	{
		wait(NULL);
		if (exec_path)
			ft_strdel(&exec_path);
		if (path)
			delete_args_array(path);
	}
	return (RC_SUCCESS);
}