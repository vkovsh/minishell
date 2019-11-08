/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:00:13 by vkovsh            #+#    #+#             */
/*   Updated: 2019/02/02 15:00:30 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bintree.h"
#include "libft.h"

t_bintree		*ft_bintree_new(const t_node *item)
{
	t_bintree	*bintree;

	if (!(bintree = (t_bintree *)malloc(sizeof(t_bintree))))
		return (NULL);
	if (!(bintree->node.value = malloc(item->value_size)))
		return (NULL);
	ft_memcpy(bintree->node.value, item->value, item->value_size);
	bintree->node.value_size = item->value_size;
	if (!(bintree->node.key = malloc(item->key_size)))
		return (NULL);
	ft_memcpy(bintree->node.key, item->key, item->key_size);
	bintree->node.key_size = item->key_size;
	bintree->left = NULL;
	bintree->right = NULL;
	bintree->height = 1;
	return (bintree);
}
