#include "minishell.h"
#include "ft_printf.h"
#include "retcode.h"
#include <signal.h>
#include "shellinfo.h"
#include "dictionary.h"

t_shellinfo	*g_si = NULL;

static void	handle_signal(int sig) 
{
	// ft_printf("Caught signal %d\n", sig);
	if (sig == SIGINT)
	{
		ft_printf("Caught signal %d\n", sig);
		display_prompt(g_si->prompt);
		//delete_shellinfo(g_si);
		//exit(0);
	}
	else if (sig == SIGQUIT)
	{
		ft_printf("Sayonara\n");
	}
	else if (sig == SIGCHLD)
	{
		ft_printf("child died\n");
	}
	else if (sig == SIGTSTP)
	{
		ft_printf("Caught signal %d\n", sig);
		display_prompt(g_si->prompt);
	}
}

static void	set_environ(t_dictionary *d, char **e)
{
	char	**p;
	char	*begin;
	t_node	node;

	begin = *e;
	while (*e)
	{
		p = ft_strsplit(*e++, '=');
		node = ITEM(*p,
					ft_strlen(*p) + 1,
					p[1],
					ft_strlen(p[1]) + 1);
		INSERT(d, &node);
		delete_args_array(p);
	}
	*e = begin;
}

static void	del_node(t_node *item, t_del_key del_k, t_del_value del_v)
{
	del_k(item->key);
	del_v(item->value);
}

void		init_shellinfo(t_shellinfo *si, char **env)
{
	char	working_dir[256];
	const t_del del_struct = (t_del){free, free, del_node};

	g_si = si;
	signal(SIGINT, &handle_signal);
	signal(SIGTSTP, &handle_signal);
	getcwd(working_dir, 256);
	si->environ = NULL;
	init_dictionary(&si->environ, ft_memcmp, ft_memcmp, &del_struct);
	set_environ(si->environ, env);
	init_dictionary(&si->history, ft_memcmp, (t_compare_keys)ft_strncmp, &del_struct);
	load_history(si);
	si->env_array = (char **)si->environ->data(si->environ);
	si->shell_exit = 0;
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