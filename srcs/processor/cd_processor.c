#include "minishell.h"
#include "ft_printf.h"
#include "retcode.h"
#include "shellinfo.h"
#include "dictionary.h"

static t_retcode	change_exec_dir(shell *s, const char *cd_path)
{
	char			buf[PATH_MAX];

	if (chdir(cd_path) == -1)
	{
		return (RC_ERR_CHDIR);
	}
	ft_strdel(&s->current_proc_path);
	s->current_proc_path =	ft_strdup(getcwd(buf, PATH_MAX));
	if (s->current_proc_path == NULL)
	{
		return (RC_ERR_MEMALLOC);
	}
	delete_string(s->prompt);
	s->prompt =	create_prompt(s->current_proc_path);
	return (RC_SUCCESS);
}

t_retcode			cd_processor(shell *s, cmd *c)
{
	char			*cd_path;
	t_retcode		ret;
	
	cd_path = NULL;
	if (c->cmd_args[1] == NULL)
	{
		cd_path = FIND(s->environ, "HOME", 4);
		ret = change_exec_dir(s, cd_path);
		return (ret);
	}
	else if (access(c->cmd_args[1], F_OK | X_OK) == -1)
	{
		ft_printf("'%s' permission denied\n", c->cmd_args[1]);
		return (RC_ERR_PERMISSION);
	}
	else
	{
		cd_path = *(c->cmd_args + 1);
		ret = change_exec_dir(s, cd_path);
		return (RC_SUCCESS);
	}
}