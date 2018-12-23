#ifndef SSTRING_H
# define SSTRING_H
# include <string.h>

typedef struct		s_string
{
	char			*str;
	size_t			size;
}					t_string;

t_string	*create_string(const char *str,
						size_t size);
t_string	*string_join(const t_string *string1,
						const t_string *string2);
void		delete_string(t_string *string);
#endif