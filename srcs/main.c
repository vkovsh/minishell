#include "minishell.h"
#include "ft_printf.h"

int				main(int ac, char **av, char **ev)
{
	char		cmd_str[128] = {0};
	ssize_t		count;
	char		*cmd_str_trimmed;
	shell		si;

	(void)ac;
	(void)av;
	cmd_str_trimmed = NULL;
	init_shellinfo(&si, ev);
	display_prompt(si.prompt);
	ft_memset(cmd_str, 0, 128);

	t_dictionary *new_dict = si.environ->clone(si.environ);
	char **test_data = (char **)si.environ->data(si.environ);
	char **test_data2 = (char **)new_dict->data(new_dict);
	ft_putchar('\n');
	while (*test_data != NULL && *test_data2 != NULL)
	{
		ft_printf("[%s]\n[%s]\n", *test_data++, *test_data2++);
	}
	if (*test_data != NULL || *test_data2 != NULL)
	{
		ft_printf("fail\n");
	}

	while ((count = read(STDIN, cmd_str, 128)))
	{
		cmd_str[count - 1] = '\0';
		if (*cmd_str)
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
			if (si.shell_exit)
				break ;
		}
		display_prompt(si.prompt);
	}
	delete_shellinfo(&si);
	return (0);
}