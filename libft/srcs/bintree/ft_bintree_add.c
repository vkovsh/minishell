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
		t_bintree *entry,
		t_compare_keys compare)
{
	if (*t == NULL)
		*t = entry;
	else
	{
		if (compare(entry->node.key, (*t)->node.key, entry->node.key_size) < 0)
			ft_bintree_add(&((*t)->left), entry, compare);
		else
			ft_bintree_add(&((*t)->right), entry, compare);
		*t = ft_balance(*t);
	}
}
