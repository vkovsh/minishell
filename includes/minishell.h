#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "ft_printf.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdint.h>
# include <unistd.h>
# include "cmd.h"
# include <stdbool.h>
# include <signal.h>
# define NAME_MAX 255
# define PATH_MAX 4096
# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct stat t_stat;

typedef struct		s_shellinfo
{
	bool			shell_exit;
	size_t			cmd_history_count;
	t_list			*cmd_history;
	t_list			*cmd_current;
	t_list			*arguments;
	t_dictionary	*environ;
	char			**env_array;
	t_processor		processors[CMD_TOTAL];
	char			*bin_path;
	char			*init_proc_path;
	char			*current_proc_path;
	t_string		*prompt;
}					t_shellinfo;

t_string			*create_prompt(const char *dir_name);
void				display_prompt(t_string *prompt);
void				init_shellinfo(t_shellinfo *si, char **ev);
void				delete_shellinfo(t_shellinfo *s);
void				delete_args_array(char **arr);
void				signal_handler(int sig_num);

#endif