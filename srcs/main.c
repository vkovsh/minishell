#include "minishell.h"
#include "ft_printf.h"

int				main(int ac, char **av, char **ev)
{
	char		*cmd_str;
	char		*cmd_str_trimmed;
	shell		si;

	(void)ac;
	(void)av;
	cmd_str_trimmed = NULL;
	// ft_printf("%s\n", ft_substrcut("\"a\"", "\""));
	init_shellinfo(&si, ev);
	display_prompt(si.prompt);
	while (si.shell_exit == 0)
	{
		cmd_str = NULL;
		get_next_line(STDIN, &cmd_str);
		if (cmd_str == NULL)
			break ;
		if (*cmd_str != '\0')
		{
			cmd_str_trimmed = ft_strtrim(cmd_str);
			if (cmd_str_trimmed && *cmd_str_trimmed)
			{
				si.cmd_current = lexer(cmd_str_trimmed, &si);
				exec(&si, si.cmd_current);
				if (!si.cmd_history)
				{
					ft_lstrev(&si.cmd_current);
					si.cmd_history = si.cmd_current;
				}
				else
					ft_lstaddsub(&si.cmd_history, si.cmd_current);
			}
			if (cmd_str_trimmed)
				ft_strdel(&cmd_str_trimmed);
		}
		ft_strdel(&cmd_str);
		display_prompt(si.prompt);
	}
	delete_shellinfo(&si);
	return (0);
}