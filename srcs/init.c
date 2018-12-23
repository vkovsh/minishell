#include "minishell.h"

void	init_shellinfo(t_shellinfo *si)
{
	si->cmd_current = NULL;
	si->cmd_history = NULL;
	si->processors[ECHO_ID] = echo_processor;
	si->processors[CD_ID] = cd_processor;
	si->processors[SETENV_ID] = setenv_processor;
	si->processors[UNSETENV_ID] = unsetenv_processor;
	si->processors[ENV_ID] = env_processor;
	si->processors[EXIT_ID] = env_processor;
}