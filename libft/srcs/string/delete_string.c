#include "libft.h"

void	delete_string(t_string *string)
{
	ft_strdel(&(string->str));
	free(string);
}