#include "minishell.h"
#include "ft_printf.h"

int			exec(void *shell, t_list *commands)
{
	t_cmd	*current;
	
	while (commands)
	{
		current = (t_cmd *)commands->content;
		current->cmd_processor(shell, current);
		if (current->cmd_status == EXEC_FAIL)
			return (0);
		commands = commands->next;
	}
	return (1);
}