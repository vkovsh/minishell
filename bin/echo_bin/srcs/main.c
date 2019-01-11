#include "libft.h"
#include "ft_printf.h"

int			main(int ac, const char **av, char **ev)
{
	size_t	length;
	char	*key;

	(void)ac;
	while ((*(++av)))
	{
		length = ft_strlen(*av);
		if (**av == '\042' && *(*av + length - 1) == '\042')
			write(1, ((*av) + 1), length - 2);
		else if (**av == '$')
		{
			ft_printf("%s\n", ft_bintree_find((t_bintree **)&ev[0],
								key,
								ft_strlen(key),
								ft_memcmp)->value);
		}
		else
			write(1, *av, length);
		if (*(av + 1))
			write(1, " ", 1);
	}
	write(1, "\n", 1);
	return (0);
}