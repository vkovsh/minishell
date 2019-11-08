#ifndef SHELLINFO_H
# define SHELLINFO_H

typedef	unsigned long size_t;
typedef struct s_list t_list;
typedef struct s_dictionary t_dictionary;
typedef struct s_shellinfo shell;
typedef struct s_cmd cmd;
typedef enum e_retcode t_retcode;
typedef struct s_string t_string;

/*
** Command processor prototype
*/
typedef t_retcode	(*t_processor)(shell *shell, cmd *cmd);
/*
** Command enumerator
*/
typedef enum		e_cmd_id
{
	INIT = -1,
	CLEAR_ID = 0,
	PWD_ID = 1,
	ECHO_ID = 2,
	CD_ID = 3,
	SETENV_ID = 4,
	UNSETENV_ID = 5,
	ENV_ID = 6,
	EXIT_ID = 7,
	ARBITRARY_ID = 8,
	CMD_TOTAL = 9,
}					t_cmd_id;

/*
** Command wrapper
*/
typedef struct		s_cmd
{
	t_cmd_id		cmd_id;
	char			*cmd_txt;
	char			*cmd_name;
	char			**cmd_args;
	size_t			cmd_args_count;
	t_processor		cmd_processor;	
}					t_cmd;

typedef struct		s_shellinfo
{
	int				history_handler;
	int				shell_exit;
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
	t_dictionary	*history;
}					t_shellinfo;

#endif