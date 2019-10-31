#include "minishell.h"
#include "ft_printf.h"
#include <termios.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/kd.h>

int				main(int ac, char **av, char **ev)
{
	static struct termios t_old, t_new;
	char		*cmd_str_trimmed;
	shell		si;
	const size_t	buff_size = 1024;
	char		cmd_str[buff_size + 1];
	
	ioctl(0, KDSKBMODE, K_MEDIUMRAW);
	tcgetattr(0, &t_old);
	t_new = t_old;
	t_new.c_lflag &= ~ICANON;
	(void)ac;
	(void)av;
	cmd_str_trimmed = NULL;
	init_shellinfo(&si, ev);
	display_prompt(si.prompt);
	while (si.shell_exit == 0)
	{
		tcsetattr(0, TCSANOW, &t_new);
		size_t buff_index = 0;
		while (read(0, cmd_str + buff_index, 1) > 0)
		{
			if (*(cmd_str + buff_index) == '\n' || buff_index == buff_size)
				break ;
			else if (*(cmd_str + buff_index) == 0x12)//ctrl+R
			{
				ft_printf("\n(reverse-i-search): ");
				break ;
			}
			else if (*(cmd_str + buff_index) == 0x04) //ctrl+D
			{
				ft_printf("EOF\n");
				exit(0);
				break ;
			}
			buff_index++;	
		}
		tcsetattr(0, TCSANOW, &t_old);
		ioctl(0, KDSKBMODE, K_XLATE);
		cmd_str[buff_index] = '\0';
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
				{
					ft_lstaddsub(&si.cmd_history, si.cmd_current);
				}
			}
			if (cmd_str_trimmed)
				ft_strdel(&cmd_str_trimmed);
		}
		display_prompt(si.prompt);
	}
	delete_shellinfo(&si);
	tcsetattr(0, TCSANOW, &t_old);
	ioctl(0, KDSKBMODE, K_XLATE);
	return (0);
}