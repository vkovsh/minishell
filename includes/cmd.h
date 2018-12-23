#ifndef CMD_H
# define CMD_H
# define CMDS {"ECHO","CD","SETENV","UNSETENV","ENV","EXIT"}
# include "libft.h"

/*
** Command processor prototype
*/
typedef int			(*t_cmd_processor)(void *cmd);

/*
** Command enumerator
*/
typedef enum		e_cmdnums
{
	UNDEFINED = -1,
	ECHO_ID,
	CD_ID,
	SETENV_ID,
	UNSETENV_ID,
	ENV_ID,
	EXIT_ID,
	CMD_TOTAL
}					t_cmdnums;

/*
** Command wrapper
*/
typedef struct		s_cmd
{
	t_cmdnums		cmd;
	t_list			*cmd_args;
	size_t			cmd_arg_count;
	t_cmd_processor	cmd_processor;	
}					t_cmd;

/*
** cmd - t_cmd struct
** Returns 0 on success and 1 if fails
*/
int					echo_processor(void *cmd);
int					cd_processor(void *cmd);
int					setenv_processor(void *cmd);
int					unsetenv_processor(void *cmd);
int					env_processor(void *cmd);
int					exit_processor(void *cmd);

/*
** Function for parsing command text
** Returns a list of t_cmd structures
*/
t_list				*lexer(t_string *cmd_txt);

#endif