#ifndef CMD_H
# define CMD_H
# define CMDS {"clear","ls","pwd","echo","cd","setenv","unsetenv","env","exit",""}
# include "libft.h"
# define SHELL struct s_shellinfo
# define CMD struct s_cmd
# define CLEAR_SCREEN_ANSI "\e[1;1H\e[2J"

struct s_shellinfo;
struct s_cmd;

/*
** Command processor prototype
*/
typedef void		(*t_processor)(SHELL *shell, CMD *cmd);

/*
** Command enumerator
*/
typedef enum		e_cmdnums
{
	INIT = -1,
	CLEAR_ID,
	LS_ID,
	PWD_ID,
	ECHO_ID,
	CD_ID,
	SETENV_ID,
	UNSETENV_ID,
	ENV_ID,
	EXIT_ID,
	ARBITRARY_ID,
	CMD_TOTAL
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
void				clear_processor(SHELL *s, CMD *c);
void				ls_processor(SHELL *s, CMD *c);
void				pwd_processor(SHELL *s, CMD *c);
void				echo_processor(SHELL *s, CMD *c);
void				cd_processor(SHELL *s, CMD *c);
void				setenv_processor(SHELL *s, CMD *c);
void				unsetenv_processor(SHELL *s, CMD *c);
void				env_processor(SHELL *s, CMD *c);
void				exit_processor(SHELL *s, CMD *c);
void				arbitrary_processor(SHELL *s, CMD *c);

/*
** Function for parsing command text
** Returns a list of t_cmd structures
*/
t_list				*lexer(const char *cmd_txt,
					t_processor	*processors);

/*
** Function for creation command entity of type t_cmd
*/
t_cmd				create_command(const char *cmd_txt,
					t_processor *ptable);

/*
** Deletes command entity
*/
void				delete_command(t_cmd *cmd);

/*
** Executes list of commands
*/
int					exec(void *shell, t_list *commands);
#endif