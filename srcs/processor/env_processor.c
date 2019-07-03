#include "minishell.h"
#include "stdlib.h"
#include "ft_printf.h"

/*
static void			print(void *k, size_t k_size,
						void *v, size_t v_size)
{
	(void)k_size;
	(void)v_size;
	ft_printf("%s=%s\n", k, v);
}*/

static uint8_t set_flag_mask(char f)
{
	t_envflags e;
	const uint8_t masks[ENV_TOTAL] = MASKS;

	e = ENV_UNDEFINED;
	while (++e < ENV_TOTAL)
		if (f == ENV_FLAGS_LITERALS[e])
			return (masks[e]);
	return (0);
}

// static void set_environ(const shell *s,
// 						const uint8_t flags,
// 						char ***environ)
// {
	// if (flags & ENV_I_M)
	// 	*environ = NULL;
	// else if (!flags)
	// int i = -1;
	// while (s->env_array[++i])
	// {
	// 	ft_printf("[[%s]]\n", s->env_array[i]);
	// }
	// (void)flags;
	// size_t env_count = SIZE(s->environ);
	// *environ = (char **)malloc(sizeof(char *) * (env_count + 1));
	// if (environ == NULL)
	// {
	// 	return ;
	// }
	
		// *environ = s->env_array;
// }

void env_processor(shell *s, cmd *c)
{
	uint8_t flags;
	int i;
	int j;
	char *cmd_name;
	char **cmd_args;
	char **cmd_environ;

	flags = 0;
	cmd_name = NULL;
	cmd_args = NULL;
	i = 0;
	char **ff = s->env_array;
	while (*ff)
	{
		ft_printf("%s\n", *ff++);
	}
	return ;
	while (c->cmd_args[++i] && *(c->cmd_args[i]) == '-')
	{
		j = 1;
		while (c->cmd_args[i][j])
		{
			flags |= set_flag_mask(c->cmd_args[i][j++]);
		}
	}
	// set_environ(s, flags, &cmd_environ);
	
	t_list	*tmp = NULL;
	size_t addition = 0;
	while (ft_strchr(c->cmd_args[i], '=') != NULL)
	{
		ft_lstadd(&tmp, ft_lstnew(c->cmd_args[i], ft_strlen(c->cmd_args[i]) + 1));
		i++;
		addition++;
	}
	size_t result_size = addition;
	if ((flags & ENV_I_M) == 0)
	{
		result_size += SIZE(s->environ);
	}
	cmd_environ = (char **)malloc(sizeof(char *) * (result_size + 1));
	cmd_environ[result_size] = NULL;
	// if (flags & ENV_I_M == 0)
	// {

	// }
	
	if (c->cmd_args[i])
		cmd_name = c->cmd_args[i];
	cmd_args = &c->cmd_args[i];
	c->cmd_status = EXEC_SUCCESS;
	if (cmd_name && !(flags & ENV_ZERO_M))
	{
		pid_t child_pid = fork();
		if (child_pid == 0)
		{
			execve(cmd_name, cmd_args, cmd_environ);
			exit(0);
		}
		else
		{
			wait(NULL);
		}
	}
	else
	{
		// if ((flags & ENV_ZERO_M) )
	}
}