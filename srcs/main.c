#include "minishell.h"
#include "ft_printf.h"
#include <termios.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <unistd.h>
#include "retcode.h"
#include "dictionary.h"
#include "shellinfo.h"

int				main(int ac, char **av, char **ev)
{
	char		*cmd_str_trimmed;
	shell		si;
	const size_t	buff_size = 1024;
	char		cmd_str[buff_size + 1];
	
	(void)ac;
	(void)av;
	cmd_str_trimmed = NULL;
	init_terminal_data();
	get_init_mode();
	set_raw_mode();
	init_shellinfo(&si, ev);
	display_prompt(si.prompt);
	while (si.shell_exit == 0)
	{
		enable_raw_mode();
		size_t buff_index = 0;
		while (read(STDIN_FILENO, cmd_str + buff_index, 1) > 0)
		{
			if (*(cmd_str + buff_index) == '\n' ||
				*(cmd_str + buff_index) == '\r' ||
				buff_index == buff_size)
			{
				write(1, "\n", 1);
				// ft_printf("Enter\n");
				break ;
			}
			else if (*(cmd_str + buff_index) == 0x12)//ctrl+R
			{
				ft_printf("\n(reverse-i-search): ");
				while (read(0, cmd_str + buff_index, 1) > 0)
				{
					if (*(cmd_str + buff_index) == '\n' || buff_index == buff_size)
					{
						break ;
					}
					else if (*(cmd_str + buff_index) == 0x04) //ctrl+D
					{
						ft_printf("EOF\n");
						exit(0);
					}
					cmd_str[buff_index + 1] = '\0';
					ft_printf("[%s]\n", cmd_str);
					char *found_cmd = FIND(si.history, cmd_str, buff_index);
					ft_printf("[[%s]]\n", found_cmd);
					buff_index++;
				}
				break ;
			}
			else if (*(cmd_str + buff_index) == 0x04) //ctrl+D
			{
				ft_printf("EOF\n");
				exit(0);
			}
			else if (*(cmd_str + buff_index) == 127) //backspace
			{
				term_goto(5, 0);
				// printf(g_key_down_str);
			}
			ft_printf("keycode = %d\n", *(cmd_str + buff_index));
			if (1 == ft_isprint(*(cmd_str + buff_index)))
			{
				write(STDOUT_FILENO, cmd_str + buff_index, 1);
			}
			buff_index++;	
		}
		disable_raw_mode();
		// tcsetattr(0, TCSANOW, &t_old);
		// ioctl(0, KDSKBMODE, K_XLATE);
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
	disable_raw_mode();
	return (0);
}