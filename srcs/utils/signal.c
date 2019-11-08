#include "minishell.h"
#include "ft_printf.h"
#include <signal.h>

void	signal_handler(int sig_num)
{
	(void)sig_num;
	system("clear");
	ft_printf("Magic... moments...\n");
	signal(SIGINT, signal_handler);
}