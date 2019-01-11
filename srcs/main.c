#include "minishell.h"

int				main(int ac, char **av, char **ev)
{
	t_shellinfo	si;
	char		cmd_str[128];
	ssize_t		count;

	(void)ac;
	(void)av;
	init_shellinfo(&si, ev);
	display_prompt(si.prompt);
	while ((count = read(STDIN, cmd_str, 128)))
	{
		cmd_str[count] = '\0';
		si.cmd_current = lexer(cmd_str, si.processors);
		exec(&si, si.cmd_current);
		if (!si.cmd_history)
		{
			ft_lstrev(&si.cmd_current);
			si.cmd_history = si.cmd_current;
		}
		else
			ft_lstaddsub(&si.cmd_history, si.cmd_current);
		if (si.shell_exit)
			break ;
		display_prompt(si.prompt);
	}
	delete_shellinfo(&si);
	return (0);
}