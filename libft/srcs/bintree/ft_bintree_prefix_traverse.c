/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintree_prefix_traverse.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkovsh <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:02:16 by vkovsh            #+#    #+#             */
/*   Updated: 2019/02/02 15:02:18 by vkovsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bintree_prefix_traverse(t_bintree **t,
		t_node_action action)
{
	if (*t == NULL)
		return ;
	action(&((*t)->node));
	ft_bintree_prefix_traverse(&((*t)->left), action);
	ft_bintree_prefix_traverse(&((*t)->right), action);
}
