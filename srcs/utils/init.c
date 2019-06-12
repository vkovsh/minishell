#include "minishell.h"
#include "ft_printf.h"

t_shellinfo	*g_si = NULL;

static void	handle_signal(int sig) 
{
	ft_printf("Caught signal %d\n", sig);
	if (sig == SIGINT)
	{ 
		delete_shellinfo(g_si);
		exit(0);
	}
}

static void	set_environ(t_dictionary *d, char **e)
{
	char	**p;
	char	*begin;

	begin = *e;
	while (*e)
	{
		p = ft_strsplit(*e++, '=');
		INSERT(d, ITEM(*p,
					ft_strlen(*p) + 1,
					p[1],
					ft_strlen(p[1]) + 1));
		delete_args_array(p);
	}
	*e = begin;
}

static void	del_node(void *k, size_t k_size,
					void *data, size_t data_size)
{
	free(k);
	free(data);
	(void)k_size;
	(void)data_size;
}

void		init_shellinfo(t_shellinfo *si, char **env)
{
	char	working_dir[256];

	g_si = si;
	signal(SIGINT, handle_signal);
	getcwd(working_dir, 256);
	si->environ = NULL;
	init_dictionary(&si->environ, ft_memcmp, del_node);
	set_environ(si->environ, env);
	si->env_array = NULL;
	si->env_array = (char **)malloc(sizeof(char *) * (SIZE(si->environ) + 1));
	si->env_array = ft_memcpy(si->env_array, env, sizeof(char *) * (SIZE(si->environ) + 1));
	si->env_array[SIZE(si->environ)] = NULL;
	si->shell_exit = false;
	si->current_proc_path = ft_strdup(working_dir);
	si->init_proc_path = ft_strdup(working_dir);
	si->bin_path = ft_strjoin(working_dir, "/bin/");
	si->prompt = create_prompt(si->current_proc_path);
	si->cmd_current = NULL;
	si->cmd_history = NULL;
	si->cmd_history_count = 0;
	si->processors[CLEAR_ID] = clear_processor;
	si->processors[PWD_ID] = pwd_processor;
	si->processors[ECHO_ID] = echo_processor;
	si->processors[CD_ID] = cd_processor;
	si->processors[SETENV_ID] = setenv_processor;
	si->processors[UNSETENV_ID] = unsetenv_processor;
	si->processors[ENV_ID] = env_processor;
	si->processors[EXIT_ID] = exit_processor;
	si->processors[ARBITRARY_ID] = arbitrary_processor;
}