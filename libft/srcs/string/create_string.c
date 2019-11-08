#include "libft.h"
#include <stdlib.h>

t_string	*create_string(const char *str,
							size_t size)
{
	t_string	*string;

	if (!(string = (t_string *)malloc(sizeof(t_string))))
		return (NULL);
	if (!(string->str = (char *)malloc(size + 1)))
		return (NULL);
	ft_strcpy(string->str, str);
	string->size = size;
	return (string);
}