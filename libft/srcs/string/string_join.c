#include "libft.h"

t_string		*string_join(const t_string *string1,
				const t_string *string2)
{
	t_string	*dst;
	size_t		dst_size;

	if (!(dst = (t_string *)malloc(sizeof(t_string))))
		return (NULL);
	dst_size = string1->size + string2->size;
	if (!(dst->str = (char *)malloc(dst_size + 1)))
		return (NULL);
	dst->size = dst_size;
	ft_memcpy(dst->str, string1->str, string1->size);
	ft_memcpy(dst->str + string1->size,
				string2->str,
				string2->size + 1);
	return (dst);
}