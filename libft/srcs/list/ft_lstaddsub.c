#include "libft.h"

void		ft_lstaddsub(t_list **alst, t_list *sub)
{
	t_list	*link;

	if (alst != NULL && sub != NULL)
	{
		link = sub;
		ft_lstrev(&sub);
		link->next = *alst;
		*alst = sub;
	}
}