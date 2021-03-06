/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_find.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:02:31 by vkovsh            #+#    #+#             */
/*   Updated: 2019/02/02 15:02:33 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bintree.h"

t_bintree		*ft_bintree_find(t_bintree **t,
				const void *key,
				const size_t key_size,
				t_compare_keys compare)
{
	t_bintree	*find;
	int			i;

	find = *t;
	while (find != NULL)
	{
		i = compare(find->node.key, key, key_size);
		if (i == 0)
		{
			return (find);
		}
		else if (i < 0)
		{
			find = find->right;
		}
		else
		{
			find = find->left;
		}
	}
	return (NULL);
}
