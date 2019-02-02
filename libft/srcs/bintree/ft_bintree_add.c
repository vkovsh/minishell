/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:04:04 by vkovsh            #+#    #+#             */
/*   Updated: 2019/02/02 15:04:10 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bintree_add(t_bintree **t,
		t_bintree *node,
		t_compare_keys compare)
{
	if (*t == NULL)
		*t = node;
	else
	{
		if (compare(node->key, (*t)->key, node->key_size) < 0)
			ft_bintree_add(&((*t)->left), node, compare);
		else
			ft_bintree_add(&((*t)->right), node, compare);
		*t = ft_balance(*t);
	}
}
