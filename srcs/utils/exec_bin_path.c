#include "minishell.h"
#include "ft_printf.h"

char        *exec_bin_path(const char *bin_name,
                            char **path)
{
	int	    i;
	char	*curr_path;

	if (access(bin_name, F_OK | X_OK) != -1)
	{
		return (ft_strdup(bin_name));
	}
	if (path == NULL)
	{
		return (NULL);
	}
	i = -1;
	while (path[++i])
	{
		curr_path = ft_strjoin_free(path[i],
			ft_strjoin("/", bin_name), 0, 1);
		if (access(curr_path, F_OK | X_OK) != -1)
			return (curr_path);
	}
	return (NULL);
}