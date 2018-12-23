#include "minishell.h"
#include <stdio.h>
#include <locale.h>

t_string		*create_prompt(void)
{
	t_string	*prompt;
	char		dir_name[256];
	char		*cut_dir_name;

	getcwd(dir_name, 256);
	cut_dir_name = ft_strrchr(dir_name, '/');
	if (cut_dir_name)
		cut_dir_name++;
	else
		cut_dir_name = dir_name;
	cut_dir_name = ft_strjoin_free(
			"\x1b[38;2;205;236;119m"
			"\U0000279C\040\040\033[1m",
		ft_strjoin_free("\x1b[38;2;0;255;239m",
		ft_strjoin_free(ft_strjoin(cut_dir_name,  "\033[1m"),
		"\x1b[38;2;255;196;0m \U00002717\040\033[0m", 1, 0), 0, 1), 0, 1);
	prompt = create_string(cut_dir_name,
		ft_strlen(cut_dir_name));
	ft_strdel(&cut_dir_name);
	return (prompt);
}