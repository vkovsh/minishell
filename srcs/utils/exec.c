#include "minishell.h"
#include "ft_printf.h"

t_retcode		exec(void *shell, t_list *commands)
{
	t_cmd		*current;
	t_retcode	ret;

	while (commands)
	{
		current = (t_cmd *)commands->content;
		ret = current->cmd_processor(shell, current);
		if (ret != RC_SUCCESS)
		{
			return (ret);
		}
		commands = commands->next;
	}
	return (ret);
}