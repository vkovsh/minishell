#include "minishell.h"

static void	set_environ(t_bintree **b, char **e)
{
	char	**kv;
	char	*begin;

	begin = *e;
	while (*e)
	{
		kv = ft_strsplit(*e++, '=');
		ft_bintree_add(b,
			ft_bintree_new(kv[0], ft_strlen(kv[0]) + 1,
			kv[1], ft_strlen(kv[1]) + 1), ft_memcmp);
		delete_args_array(kv);
	}
	*e = begin;
}

void		init_shellinfo(t_shellinfo *si, char **env)
{
	char	working_dir[256];

	getcwd(working_dir, 256);
	si->env_array = env;
	si->environ = NULL;
	set_environ(&si->environ, env);
	si->shell_exit = false;
	si->current_proc_path = ft_strdup(working_dir);
	si->init_proc_path = ft_strdup(working_dir);
	si->bin_path = ft_strjoin(working_dir, "/bin/");
	si->prompt = create_prompt(si->current_proc_path);
	si->cmd_current = NULL;
	si->cmd_history = NULL;
	si->cmd_history_count = 0;
	si->processors[CLEAR_ID] = clear_processor;
	si->processors[LS_ID] = ls_processor;
	si->processors[PWD_ID] = pwd_processor;
	si->processors[ECHO_ID] = echo_processor;
	si->processors[CD_ID] = cd_processor;
	si->processors[SETENV_ID] = setenv_processor;
	si->processors[UNSETENV_ID] = unsetenv_processor;
	si->processors[ENV_ID] = env_processor;
	si->processors[EXIT_ID] = exit_processor;
	si->processors[ARBITRARY_ID] = arbitrary_processor;
}