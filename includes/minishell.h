#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdint.h>
# include <unistd.h>
# include <stdbool.h>
# include <signal.h>
# include "retcode.h"
# define NAME_MAX 255
# define PATH_MAX 4096
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define ENV_I_M 0x01
# define ENV_ZERO_M 0x02
# define ENV_U_M 0x04
# define ENV_C_M 0x08
# define MASKS {ENV_I_M, ENV_ZERO_M, ENV_U_M, ENV_C_M}
# define ENV_FLAGS_LITERALS "i0uC"
# define SHELL_BUFF_SIZE 128

typedef struct s_list t_list;
typedef struct s_dictionary t_dictionary;
typedef struct s_string t_string;
struct s_shellinfo;
struct s_cmd;
typedef struct stat t_stat;
typedef struct s_shellinfo shell;
typedef struct s_cmd cmd;

/*
** 	-i, --ignore-environment
**		start with an empty environment
**
** 	-0, --null
**		end each output line with NUL, not newline
**
**	-u, --unset=NAME
**		remove variable from the environment
**
**	-C, --chdir=DIR
**		change working directory to DIR
*/
typedef enum		e_envflags
{
	ENV_UNDEFINED = -1,
	ENV_I = 0,
	ENV_ZERO = 1,
	ENV_U = 2,
	ENV_C = 3,
	ENV_TOTAL = 4
}					t_envflags;

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
	char			*cmd_name;
	char			**cmd_args;
	size_t			cmd_args_count;
	t_processor		cmd_processor;	
}					t_cmd;

/*
** cmd - t_cmd struct
** Returns 0 on success and 1 if fails
*/
t_retcode			clear_processor(shell *s, cmd *c);
t_retcode			pwd_processor(shell *s, cmd *c);
t_retcode			echo_processor(shell *s, cmd *c);
t_retcode			cd_processor(shell *s, cmd *c);
t_retcode			setenv_processor(shell *s, cmd *c);
t_retcode			unsetenv_processor(shell *s, cmd *c);
t_retcode			env_processor(shell *s, cmd *c);
t_retcode			exit_processor(shell *s, cmd *c);
t_retcode			arbitrary_processor(shell *s, cmd *c);

/*
** Function for parsing command text
** Returns a list of t_cmd structures
*/
t_list				*lexer(const char *cmd_txt, shell *s);

/*
** Function for creation command entity of type t_cmd
*/
t_cmd				create_command(const char *cmd_txt, shell *s);

/*
** Deletes command entity
*/
void				delete_command(cmd *cmd);

/*
** Executes list of commands
*/
t_retcode					exec(void *shell, t_list *commands);

typedef struct		s_shellinfo
{
	int				history_handler;
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
	t_dictionary	*history;
}					t_shellinfo;

t_string			*create_prompt(const char *dir_name);
void				display_prompt(t_string *prompt);
void				init_shellinfo(t_shellinfo *si, char **ev);
void				delete_shellinfo(t_shellinfo *s);
void				delete_args_array(char **arr);
void				signal_handler(int sig_num);

t_retcode           load_history(shell *s);

char				*exec_bin_path(const char *bin_name,
						char **path);
#endif