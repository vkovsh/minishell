#include "libft.h"

t_bintree		*findmin(t_bintree *p)
{
	return (p->left ? findmin(p->left) : p);
}

t_bintree		*removemin(t_bintree *p)
{
	if (p->left == NULL)
		return (p->right);
	p->left = removemin(p->left);
	return (ft_balance(p));
}

t_bintree		*ft_bintree_remove(t_bintree *p,
				void *key,
				size_t key_size,
				t_compare_keys cmp,
				t_del_node del)
{
	int			cmp_res;
	t_bintree	*q;
	t_bintree	*r;
	t_bintree	*min;

	if (!p)
		return (NULL);
	if ((cmp_res = cmp(key, p->key, key_size)) < 0)
		p->left = ft_bintree_remove(p->left, key,
					key_size, cmp, del);
	else if (cmp_res > 0)
		p->right = ft_bintree_remove(p->right, key,
					key_size, cmp, del);
	else
	{
		q = p->left;
		r = p->right;
		ft_bintree_delone(&p, del);
		if (!r)
			return (q);
		min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return (ft_balance(min));
	}
	return (ft_balance(p));
}