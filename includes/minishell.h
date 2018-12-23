#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "ft_printf.h"
# include <sys/stat.h>
# include <stdint.h>
# include <unistd.h>
# include "cmd.h"

typedef struct stat t_stat;

typedef struct		s_shellinfo
{
	t_list			*cmd_history;
	t_list			*cmd_current;
	t_cmd_processor	processors[CMD_TOTAL];
}					t_shellinfo;

t_string			*create_prompt(void);
void				display_prompt(t_string *prompt);
void				init_shellinfo(t_shellinfo *si);

#endif