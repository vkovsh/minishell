/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_remove.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:02:50 by vkovsh            #+#    #+#             */
/*   Updated: 2019/02/02 15:02:52 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
					const void *key,
					const size_t key_size,
					t_compare_keys cmp,
					t_del *del_struct)
{
	int			cmp_res;
	t_bintree	*q;
	t_bintree	*r;
	t_bintree	*min;

	if (p == NULL)
		return (NULL);
	cmp_res = cmp(key, p->node.key, key_size);
	if (cmp_res < 0)
	{
		p->left = ft_bintree_remove(p->left, key,
					key_size, cmp, del_struct);
	}
	else if (cmp_res > 0)
	{
		p->right = ft_bintree_remove(p->right, key,
					key_size, cmp, del_struct);
	}
	else
	{
		q = p->left;
		r = p->right;
		ft_bintree_delone(&p, del_struct);
		if (!r)
			return (q);
		min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return (ft_balance(min));
	}
	return (ft_balance(p));
}
