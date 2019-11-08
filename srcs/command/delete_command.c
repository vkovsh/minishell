#include "minishell.h"
#include "ft_printf.h"
#include "shellinfo.h"

void	delete_command(t_cmd *cmd)
{
	ft_strdel(&(cmd->cmd_txt));
	// (void)cmd;
}