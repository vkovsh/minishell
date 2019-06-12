#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdint.h>
# include <unistd.h>
# include <stdbool.h>
# include <signal.h>
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
	ENV_I,
	ENV_ZERO,
	ENV_U,
	ENV_C,
	ENV_TOTAL
}					t_envflags;

/*
** Command processor prototype
*/
typedef void		(*t_processor)(shell *shell, cmd *cmd);

/*
** Command enumerator
*/
typedef enum		e_cmdnums
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
}					t_cmdnums;

/*
** Command status enumerator
*/
typedef enum		s_cmdstatus
{
	EXEC_READY,
	EXEC_SUCCESS,
	EXEC_FAIL
}					t_cmdstatus;

/*
** Command wrapper
*/
typedef struct		s_cmd
{
	t_cmdnums		cmd_id;
	char			*cmd_name;
	t_cmdstatus		cmd_status;
	char			**cmd_args;
	t_processor		cmd_processor;	
}					t_cmd;

/*
** cmd - t_cmd struct
** Returns 0 on success and 1 if fails
*/
void				clear_processor(shell *s, cmd *c);
void				pwd_processor(shell *s, cmd *c);
void				echo_processor(shell *s, cmd *c);
void				cd_processor(shell *s, cmd *c);
void				setenv_processor(shell *s, cmd *c);
void				unsetenv_processor(shell *s, cmd *c);
void				env_processor(shell *s, cmd *c);
void				exit_processor(shell *s, cmd *c);
void				arbitrary_processor(shell *s, cmd *c);

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
int					exec(void *shell, t_list *commands);

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