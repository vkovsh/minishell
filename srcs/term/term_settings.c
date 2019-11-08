#include "minishell.h"
#include <termios.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <linux/kd.h>
#include <stdlib.h>
#include "retcode.h"
#include <unistd.h>

struct termios	g_init;
struct termios	g_raw;

t_retcode		disable_raw_mode(void)
{
	if (-1 == tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_init))
		return (RC_ERR_BAD_TERM_SET);
	return (RC_SUCCESS);
}

t_retcode			get_init_mode(void)
{
	if (-1 == tcgetattr(STDIN_FILENO, &g_init))
		return (RC_ERR_BAD_TERM_GET);
	return (RC_SUCCESS);
}

void				set_raw_mode(void)
{
	g_raw = g_init;
	g_raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	// g_raw.c_oflag &= ~(OPOST);
	g_raw.c_cflag |= (CS8);
	g_raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	// g_raw.c_cc[VMIN] = 0;
	// g_raw.c_cc[VTIME] = 10;
}

t_retcode			enable_raw_mode(void)
{
	if (0 != atexit((void(*)(void))disable_raw_mode))
		return (RC_ERR_BAD_EXIT_REGISTER);
	if (-1 == tcsetattr(STDIN_FILENO, TCSANOW, &g_raw))
		return (RC_ERR_BAD_TERM_SET);
	return (RC_SUCCESS);
}